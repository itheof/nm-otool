/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:04:49 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/19 11:23:15 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include "common.h"

t_file						check_header(t_mapping map)
{
	if (is_large_enough(map, map.addr, sizeof(t_magic)))
	{
		if (*(t_magic *)map.addr == FAT_CIGAM &&
				is_large_enough(map, map.addr, sizeof(struct fat_header)))
			return (fat_pre_check(map));
		else if (*(t_magic *)map.addr == FAT_CIGAM_64)
		{
			ft_puterr(NULL, "Fat format 64 unsupported");
		}
		else if (*(t_magic *)map.addr == MH_CIGAM)
		{
			;
		}
		else if (*(t_magic *)map.addr == MH_CIGAM_64)
		{
			;
		}
		else
			ft_puterr(NULL, "The file was not recognized "
					"as a valid object file");
	}
	else
		ft_puterr(NULL, "The file was not recognized "
				"as a valid object file");
	return (E_FILE_INVALID);
}
