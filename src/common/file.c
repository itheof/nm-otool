/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:10:50 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 17:38:14 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "common.h"
#include "libft/string.h"
#include "libft/buffer.h"
#include "libft/print.h"
#include "libft/libc.h"

void			unmap_file(t_mapping *map)
{
	if (!map->mallocd)
	{
		munmap((void*)map->addr, map->size);
	}
}

off_t			map_get_offset(t_mapping map, void const *addr)
{
	return ((char const *)addr - (char const *)map.addr);
}

t_bool			is_eof(t_mapping map, void const *addr)
{
	return (map.size + (char const *)map.addr == addr);
}

t_bool			is_large_enough(t_mapping map, void const *addr, size_t size)
{
	size_t	offset;

	offset = (char*)addr - (char*)map.addr;
	if (map.size >= offset + size)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}
