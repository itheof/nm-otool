/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/19 16:00:21 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include "libft/buffer.h"
#include "libft/swap.h"
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
			if (!fat_get_default_arch(map, &addr))
				return (false);
			if (addr == NULL)
			{
				while (true)
				{
					if (!fat_get_next_arch(map, &addr))
					{
						success = false;
						break;
					}
					if (addr == NULL)
						break;
					success &= process_arch(addr);
				}
				fat_get_next_arch(map, NULL);
			}
			else
				success &= process_arch(addr);*/

/*
** uint32_t == typeof((*fat)->magic)
*/

t_bool	fat_pre_check(t_mapping map)
{
	struct fat_header const	*fat;
	t_buffer				err;
	uint32_t				narch;

	buffer_init_with(&err, "truncated or malformed fat file");
	fat = map.addr;
	narch = swap_long(fat->nfat_arch);
	if (narch == 0)
		buffer_cat(&err, " (contains zero architecture types)");
	else if (!is_large_enough(map, fat + 1, sizeof(struct fat_arch) * narch))
		buffer_cat(&err, " (fat_arch structs would extend"
				" past the end of the file)");
	else
	{
		buffer_deinit(&err);
		return (true);
	}
	if (err.str != NULL)
		ft_puterr(NULL, err.str);
	buffer_deinit(&err);
	return (false);
}
