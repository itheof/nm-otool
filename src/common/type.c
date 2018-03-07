/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:04:49 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/07 10:58:02 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <ar.h>
#include "common.h"
#include "libft/stdbool.h"
#include "libft/libc.h"

/*
** *addr must point to a location in the mapping.
*/
static t_bool	is_ar_header(t_mapping map, void const *addr)
{
	return(is_large_enough(map, map.addr, SARMAG) &&
			ft_memcmp(addr, ARMAG, SARMAG) == 0);
}

t_file	get_file_type(t_mapping map, void const *addr)
{
	t_magic	num;
	
	if (is_ar_header(map, addr))
		return (E_FILE_AR);
	else if (is_large_enough(map, addr, sizeof(num)))
	{
		num = *(t_magic const *)addr;
		if (num == FAT_CIGAM)
			return (E_FILE_FAT);
		else if (num == FAT_CIGAM_64)
			return (E_FILE_FAT_64);
		else if (num == MH_MAGIC)
			return (E_FILE_MACH_O);
		else if (num == MH_MAGIC_64)
			return (E_FILE_MACH_O_64);
	}
	return (E_FILE_INVALID);
}
