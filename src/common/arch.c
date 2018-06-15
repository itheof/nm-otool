/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 09:41:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 18:29:41 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/arch.h>
#include "libft/stdbool.h"
#include "libft/buffer.h"
#include "libft/print.h"
#include "libft/libc.h"
#include "common.h"

t_bool			arch_from_default(t_list **dst)
{
	const NXArchInfo	*info;

	if ((info = NXGetArchInfoFromName("x86_64")))
	{
		if ((*dst = ft_lstnewcopy((void *)info, sizeof(*info))) == NULL)
		{
			NXFreeArchInfo(info);
			return (false);
		}
	}
	return (true);
}

static t_err	arch_create_link(t_list **dst, char const *arg)
{
	const NXArchInfo	*info;

	if ((info = NXGetArchInfoFromName(arg)) == NULL)
		return (E_ERR_INVALID_ARCH);
	if ((*dst = ft_lstnewcopy((void*)info, sizeof(*info))) == NULL)
	{
		NXFreeArchInfo(info);
		return (E_ERR_MALLOC);
	}
	return (E_ERR_NONE);
}

t_err			arch_push_arg(t_list **lsth, char const *arg)
{
	t_list	*current;

	if (*lsth)
	{
		current = *lsth;
		while (current)
		{
			if (!ft_strcmp(((const NXArchInfo *)current->content)->name, arg))
				return (E_ERR_NONE);
			if (current->next == NULL)
				break ;
			current = current->next;
		}
		return (arch_create_link(&(current->next), arg));
	}
	else
		return (arch_create_link(lsth, arg));
}

t_bool			arch_deinit(t_list *archs)
{
	t_list *next;

	if (archs == NULL)
		return (false);
	if (archs->content == DEFAULT_ARCH)
	{
		free(archs);
		return (false);
	}
	while (archs != NULL)
	{
		next = archs->next;
		NXFreeArchInfo(archs->content);
		free(archs);
		archs = next;
	}
	return (false);
}

t_bool			arch_fatal_err(char const *name, t_list *archs, char const *arg,
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
