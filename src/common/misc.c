/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:50:26 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/12 16:02:09 by tvallee          ###   ########.fr       */
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
	static char const	*p = NULL;

	if (prefix == NULL)
	{
		ft_putstr_fd(p, 2);
		ft_putstr_fd(msg, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		p = prefix;
	}
}

void	print_path(char const *path)
{
	ft_putchar(10);
	ft_putstr(path);
	ft_putendl(":");
}

t_bool	is_large_enough(t_mapping map, void *addr, size_t size)
{
	if (map.size < (size_t)((char*)addr - ((char*)map.addr + size)))
		return (true);
	else
		return (false);
}
