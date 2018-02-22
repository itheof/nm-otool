/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:04:49 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/22 16:55:24 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <ar.h>
#include "common.h"
#include "libft/stdbool.h"
#include "libft/libc.h"

/*
** *addr must point to a valid memory location.
*/
static t_bool	is_ar_header(t_mapping map, void const *addr)
{
	return(*(char const *)addr == ARMAG[0] &&
			is_large_enough(map, map.addr, SARMAG) &&
			ft_memcmp(addr, ARMAG, SARMAG) == 0);
}

t_file	get_file_type(t_mapping map, void const *addr)
{
	t_magic	num;

	num = *(t_magic const *)addr;
	if (is_large_enough(map, addr, sizeof(t_magic)))
	{
		if (num == FAT_CIGAM)
			return (E_FILE_FAT);
		else if (num == FAT_CIGAM_64)
			return (E_FILE_FAT_64);
		else if (num == MH_CIGAM)
			return (E_FILE_MACH_O);
		else if (num == MH_CIGAM_64)
			return (E_FILE_MACH_O_64);
		else if (is_ar_header(map, addr))
			return (E_FILE_AR);
		else
			ft_puterr(NULL, ERR_INVALID);
	}
	else
		ft_puterr(NULL, ERR_INVALID);
	return (E_FILE_INVALID);
}
