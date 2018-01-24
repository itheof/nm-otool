/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:10:50 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/04 16:00:40 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "misc.h"

void	ft_perror(char const *name)
{
	char buf[64];

	*buf = 0;
	ft_strcat(name);
	ft_strcat(": ");
	ft_strcat("strerror not allowed\n");
	ft_putendl_fd(buf, stderr);
}

t_bool	map_file(int fd, t_mapping *map)
{
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
	{
		PERROR("fstat");
		return (false);
	}
	map->size = buf.st_size;
	map->
	if (pe)
}
