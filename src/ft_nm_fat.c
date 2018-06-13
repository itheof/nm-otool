/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:30:25 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 18:27:35 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool	nm_handle_fat_obj(t_mapping map, t_out out, t_list *arch)
{
	t_file	type;

	type = get_file_type(map);
	if (type == E_FILE_MACH_O)
		return (nm_mach_wrap(map, out, arch));
	else if (type == E_FILE_MACH_O_64)
		return (nm_mach64_wrap(map, out, arch));
	else if (type == E_FILE_AR)
		return (nm_ar_wrap(map, out, arch));
	return (true);
}

t_bool			nm_fat_wrap(t_mapping map, t_out out, t_list *arch, t_bool all_archs)
{
	t_fat	obj;
	NXArchInfo	*info;

	obj.is_64 = false;
	obj.arch = arch;
	obj.all_archs = all_archs;
	if (!fat_init(map, &obj))
		return (false);
	return (fat_iter(&obj, &nm_handle_fat_obj, map, out));
}

t_bool			nm_fat64_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs)
{
	t_fat	obj;

	obj.is_64 = true;
	obj.arch = arch;
	obj.all_archs = all_archs;
	if (!fat_init(map, &obj))
		return (false);
	return (fat_iter(&obj, &nm_handle_fat_obj, map, out));
}
