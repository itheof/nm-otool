/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/22 17:09:09 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
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
/*
fat_init fails if none is found
t_bool	fat_invoke_all(t_mapping map)
{

}

t_bool	fat_invoke_with(t_mapping map, NXArchInfo const *info, t_out out,
		t_fun f)
{
	
}
*/

/*
				is_large_enough(map, map.addr, sizeof(struct fat_header)))
			return (fat_pre_check(map) ? E_FILE_FAT : E_FILE_INVALID);
			*/
/*
			if (env.all_archs && type == E_FILE_FAT && fat_get_narchs(map) > 1)
			;// process all available archs in the file. (use cpucode etc in header to get arch name)
		else if (env.narchs > 1)
		{
			while (true)
			{
				break;
			}
			// iter until failure over all requested archs
		}
		else
			;//success = ft_nm_(type == E_FILE_FAT) ? fat_invoke_with() : );// just for the current arch.
	}
	else
		success = nm_ar_wrap(map, map.addr, );
	return (success);
}
*/

size_t	fat_get_narchs(t_mapping map)
{
	return (swap_long(((struct fat_header const *)(map.addr))->nfat_arch));
}

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
