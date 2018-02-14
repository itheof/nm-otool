/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:04:49 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/14 11:24:14 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include "common.h"

t_bool	check_header(t_mapping map,
		struct fat_header **fat, struct mach_header_64 **mach)
{
	if (is_large_enough(map, map.addr, sizeof((*fat)->magic)))
	{
		if (*(uint32_t *)map.addr == FAT_CIGAM &&
				is_large_enough(map, map.addr, sizeof(**fat)))
			return (fat_check_header(map, fat));
		else if (*(uint32_t *)map.addr == FAT_CIGAM_64)
		{
			ft_puterr(NULL, "Fat format 64 unsupported");
		}
		else if (*(uint32_t *)map.addr == MH_CIGAM)
		{
			;
		}
		else if (*(uint32_t *)map.addr == MH_CIGAM_64)
		{
			;
		}
		else
			ft_puterr(NULL, "The file was not recognized "
					"as a valid object file");
	}
	return (false);
}
