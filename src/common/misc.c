/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:50:26 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/14 12:26:52 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print.h"
#include "libft/string.h"
#include "libft/stdbool.h"
#include "common.h"

void	ft_perror(char const *name)
{
	char buf[64];

	if (!ft_strcmp(name, ""))
	{
		ft_strcat(buf, name);
		ft_strcat(buf, ": ");
	}
	ft_strcat(buf, "strerror not allowed\n");
	ft_putendl_fd(buf, 2);
}

void	ft_puterr(char const *prefix, char const *msg)
{
	static char	*p = NULL;

	if (prefix != NULL)
	{
		free(p);
		p = ft_strdup(prefix);
	}
	else if (msg != NULL)
	{
		if (p)
			ft_putstr_fd(p, 2);
		else
			ft_putstr_fd("WARNING IN FT_PUTERR: NO P SET: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		free(p);
		p = NULL;
	}
}

void	print_path(char const *path)
{
	ft_putchar(10);
	ft_putstr(path);
	ft_putendl(":");
}
