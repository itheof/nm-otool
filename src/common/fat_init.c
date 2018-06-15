/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 10:22:04 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 18:35:01 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

static t_bool	fat_check_header(t_mapping map, uint32_t *narch, t_bool is_64)
{
	struct fat_header const	*fat;
	t_buffer				err;

	buffer_init_with(&err, "truncated or malformed fat file");
	fat = map.addr;
	*narch = swap_long(fat->nfat_arch);
	if (*narch == 0)
		buffer_cat(&err, " (contains zero architecture types)");
	else if (!is_large_enough(map, fat + 1,
				(is_64 ? sizeof(struct fat_arch_64) :
				sizeof(struct fat_arch) * *narch)))
		buffer_cat(&err, " (fat_arch structs would extend"
				" past the end of the file)");
	else if (*narch > MAX_FAT_ARCH)
		buffer_cat(&err, " (too many fat_arch structs for this build)");
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

static void		fat_register_arch(struct fat_arch_64 *dst, void const *addr,
		uint32_t i, t_bool is_64)
{
	struct fat_arch_64 const	*p1;
	struct fat_arch const		*p2;

	addr = (const char *)addr + sizeof(struct fat_header);
	if (is_64)
	{
		p1 = (struct fat_arch_64 const*)((char const *)addr + i
				* sizeof(struct fat_arch_64));
		dst->cputype = swap_long(p1->cputype);
		dst->cpusubtype = swap_long(p1->cpusubtype);
		dst->offset = swap_longlong(p1->offset);
		dst->size = swap_longlong(p1->size);
		dst->align = swap_long(p1->align);
	}
	else
	{
		p2 = (struct fat_arch const*)((char const *)addr +
				i * sizeof(struct fat_arch));
		dst->cputype = swap_long(p2->cputype);
		dst->cpusubtype = swap_long(p2->cpusubtype);
		dst->offset = swap_long(p2->offset);
		dst->size = swap_long(p2->size);
		dst->align = swap_long(p2->align);
	}
}

static t_bool	fat_parse_arch(t_mapping map, t_fat *obj, uint32_t i)
{
	fat_register_arch(obj->arr + i, map.addr, i, obj->is_64);
	if (!is_large_enough(map, (char const *)map.addr + obj->arr[i].offset,
				obj->arr[i].size))
	{
		ft_puterr(NULL, " truncated or malformed fat file"
				" (fat object extends past the end of the file)");
		return (false);
	}
	return (true);
}

t_bool			fat_init(t_mapping map, t_fat *obj)
{
	uint32_t		i;

	if (!is_large_enough(map, map.addr, sizeof(struct fat_header)))
	{
		ft_puterr(NULL, ERR_INVALID);
		return (false);
	}
	if (!fat_check_header(map, &(obj->narchs), obj->is_64))
		return (false);
	i = 0;
	while (i < obj->narchs)
	{
		if (!fat_parse_arch(map, obj, i))
			return (false);
		i++;
	}
	return (true);
}
