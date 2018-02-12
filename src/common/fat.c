/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/12 11:40:48 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include "common.h"

/*
t_bool	fat_get_default_arch(t_mapping map, struct fat_arch_64 **addr)
{
	struct fat_header	*header;

	header = map.addr;
	if (!is_large_enough(map, header, sizeof((*addr)->magic)))
		return (NULL);
	else if ((*addr)->magic == FAT_MAGIC)
	{
		if (!is_large_enough(map, (*addr), sizeof(struct fat_header)))
			return (NULL);
	}
	else if ((*addr)->magic == FAT_MAGIC_64)
		; no support atm 
	return (NULL);
}
*/

/*
** uint32_t == typeof((*fat)->magic)
*/

t_bool	check_header(t_mapping map,
		struct fat_header **fat, struct mach_header_64 **mach)
{
	if (is_large_enough(map, map.addr, sizeof((*fat)->magic)))
	{
		if (*(uint32_t *)map.addr == FAT_MAGIC)
		{
			;
		}
		else if (*(uint32_t *)map.addr == FAT_MAGIC_64)
		{
			ft_puterr(NULL, "Fat format 64 unsupported");
		}
		else if (*(uint32_t *)map.addr == MH_MAGIC)
		{
			;
		}
		else if (*(uint32_t *)map.addr == MH_MAGIC_64)
		{
			;
		}
	}
	ft_puterr(NULL, "The file was not recognized as a valid object file");
	return (false);
}
