/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_fat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:30:25 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 18:27:35 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static t_bool	otool_handle_fat_obj(t_mapping map, t_out out, t_list *arch)
{
	t_file		type;
	uint32_t	magic;

	type = get_file_type(map);
	if (type == E_FILE_MACH_O)
		return (otool_mach_wrap(map, out, arch));
	else if (type == E_FILE_MACH_O_64)
		return (otool_mach64_wrap(map, out, arch));
	else if (type == E_FILE_AR)
		return (otool_ar_wrap(map, out, arch));
	else
	{
		if (is_large_enough(map, map.addr, sizeof(magic)))
		{
			if ((magic = *(uint32_t const *)map.addr) == MH_CIGAM ||
					magic == MH_CIGAM_64)
			{
				ft_puterr(NULL, "unsupported big-endian arch in fat file");
				return (false);
			}
		}
		ft_puterr(NULL, "invalid fat object");
		return (false);
	}
}

t_bool			otool_fat_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs)
{
	t_fat	obj;

	obj.is_64 = false;
	obj.arch = arch;
	obj.all_archs = all_archs;
	if (!fat_init(map, &obj))
		return (false);
	return (fat_iter(&obj, &otool_handle_fat_obj, map, out));
}

t_bool			otool_fat64_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs)
{
	t_fat	obj;

	obj.is_64 = true;
	obj.arch = arch;
	obj.all_archs = all_archs;
	if (!fat_init(map, &obj))
		return (false);
	return (fat_iter(&obj, &otool_handle_fat_obj, map, out));
}
