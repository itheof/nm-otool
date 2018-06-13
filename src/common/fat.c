/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 16:57:18 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

t_file	ft_fat_is_fat(t_mapping map)
{
	if (is_large_enough(map, map.addr, sizeof(t_magic)) &&
			(*(t_magic*)map.addr == FAT_CIGAM ||
			*(t_magic*)map.addr == FAT_CIGAM_64))
		return (true);
	return (E_FILE_INVALID);
}
