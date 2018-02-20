/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:41:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/20 12:03:06 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/arch.h>
#include "libft/stdbool.h"
#include "libft/buffer.h"
#include "libft/print.h"
#include "common.h"

t_err	arch_push_arg(t_list **lsth, char const *arg)
{
	const NXArchInfo	*info;
	t_list				*link;

	if ((info = NXGetArchInfoFromName(arg)) == NULL)
		return (E_ERR_INVALID_ARCH);
	if ((link = ft_lstnewcopy((void*)info, sizeof(*info))) == NULL)
		return (E_ERR_MALLOC);
	ft_lstpushback(lsth, link);
	return (E_ERR_NONE);
}

void	arch_deinit(t_list *archs)
{
	t_list *next;

	while (archs != NULL)
	{
		next = archs->next;
		NXFreeArchInfo(archs->content);
		free(archs);
		archs = next;
	}
}

t_bool	arch_fatal_err(char const *name, t_list *archs, char const *arg,
		t_err err)
{
	t_buffer	buf;

	if (err == E_ERR_MALLOC)
	{
		arch_deinit(archs);
		PERROR("malloc");
		return (true);
	}
	else if (err == E_ERR_INVALID_ARCH)
	{
		if (buffer_init(&buf))
		{
			buffer_cat(&buf, name);
			buffer_cat(&buf, ": for the -arch option: "
					"Unknown architechture named '");
			buffer_cat(&buf, arg);
			buffer_cat(&buf, "'.\n");
			ft_putstr_fd(buf.str, 2);
			buffer_deinit(&buf);
		}
	}
	return (false);
}
