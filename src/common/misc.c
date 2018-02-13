/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:50:26 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/13 11:37:09 by tvallee          ###   ########.fr       */
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

t_bool	is_large_enough(t_mapping map, void *addr, size_t size)
{
	size_t	offset;

	offset = (char*)addr - (char*)map.addr;
	if (map.size >= offset + size)
	{
/*		printf("%s sized %zu, can hold enough for %zu at offset %zu\n", map.path,
				map.size, size,
				(size_t)((char*)addr - ((char*)map.addr)));*/
		return (true);
	}
	else
	{
/*		printf("%s sized %zu, can NOT hold enough for %zu at offset %zu",
				map.path, map.size, size,
				(size_t)((char*)addr - ((char*)map.addr)));*/
		return (false);
	}
}
