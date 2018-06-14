/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach-o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:23:22 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/29 15:29:57 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

static t_bool	ft_mach_load(t_mach *dst, t_mapping map)
{
	if (dst->symtab_lc != NULL && !ft_mach_load_symtab(dst, map))
		return (false);
	return (true);
}

static t_bool	ft_mach_register_mach_hdr(t_mach *dst, t_mapping map)
{
	dst->header.b64 = map.addr;
	if (!is_large_enough(map, dst->header.b64 + 1, dst->header.b64->sizeofcmds))
		return (ft_mach_err_sizeofcmds_lt_file());
	return (true);
}

t_bool			ft_mach_init(t_mach *dst, t_mapping map, t_file type)
{
	int i;

	i = 0;
	dst->is_64 = (type == E_FILE_MACH_O_64);
	if (!ft_mach_register_mach_hdr(dst, map))
		return (false);
	while (i < MAX_SECT)
		dst->sections[i++].b64 = NULL;
	dst->symtab_lc = NULL;
	if (!ft_mach_register_lc(dst))
		return (false);
	if (!ft_mach_load(dst, map))
		return (false);
	//TODO: Urgent check sections size so that we can display them easily in otool
	return (true);
}
