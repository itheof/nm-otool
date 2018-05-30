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

static void	ft_mach_dump_mach_header(struct mach_header_64 const *hdr)
{
	dprintf(2,
		"struct mach_header {\n"
		"	uint32_t	magic; /* 0x%x */\n"
		"	cpu_type_t	cputype; /* 0x%x */\n"
		"	cpu_subtype_t	cpusubtype; /* 0x%x */\n"
		"	uint32_t	filetype; /* 0x%x */\n"
		"	uint32_t	ncmds; /* 0x%x */\n"
		"	uint32_t	sizeofcmds; /* 0x%x */\n"
		"	uint32_t	flags; /* 0x%x */\n"
		"};", hdr->magic, hdr->cputype, hdr->cpusubtype,
			hdr->filetype, hdr->ncmds, hdr->sizeofcmds, hdr->flags);
}

static t_bool	ft_mach_load(t_mach *dst, t_mapping map)
{
	int i;

	/* load symtable */
	if (dst->symtab_lc != NULL && !ft_mach_load_symtab(dst, map))
		return (false);
	/*
	i = 0;
	while (dst->segment_lc[i].b64 != NULL)
	{
		if (dst->is_64)
		{
			if (!ft_mach_load_segment_64(dst, map, dst->segment_lc[i].b64))
				return (false);
		}
		else
		{
			if (!ft_mach_load_segment(dst, map, dst->segment_lc[i].b32))
				return (false);
		}
		i++;
	}*/
	return (true);
}

static t_bool	ft_mach_register_mach_hdr(t_mach *dst, t_mapping map)
{
	dst->header = map.addr;
	//ft_mach_dump_mach_header(dst->header);
	if (!is_large_enough(map, dst->header + 1, dst->header->sizeofcmds))
		return (ft_mach_err_sizeofcmds_lt_file());
	return (true);
}

t_bool	ft_mach_init(t_mach *dst, t_mapping map, t_file type)
{
	if (!ft_mach_register_mach_hdr(dst, map))
		return (false);
	dst->is_64 = (type == E_FILE_MACH_O_64);
	for (int i = 0; i < MAX_SECT; i++)
		dst->sections[i].b64 = NULL;
	if (!ft_mach_register_lc(dst))
		return (false);
	if (!ft_mach_load(dst, map))
		return (false);
	return (true);
}
