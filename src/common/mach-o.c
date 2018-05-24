/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach-o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:23:22 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/23 18:56:20 by tvallee          ###   ########.fr       */
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

/*
** TODO:  parse the commands according to the type. Once type is known check the
size
*/

static t_bool	ft_mach_validate_lc(t_mach *dst)
{
	uint32_t					remaining;
	uint32_t					n;
	struct load_command const	*current;

	if (dst->is_64)
		dst->lc_start = (struct load_command const *)(dst->header + 1);
	else
		dst->lc_start = (struct load_command const *)(
				(char const *)dst->header - sizeof(struct mach_header));

	remaining = dst->header->sizeofcmds;
	current = dst->lc_start;
	n = 0;
	while (n < dst->header->ncmds)
	{
		if (remaining < sizeof(*current))
			return (ft_mach_err_lc_past_all_cmds(n));
		else if (current->cmdsize & (0x08 - 1))
			return (ft_mach_err_lc_size_not_aligned(n));
		else if (current->cmdsize < sizeof(*current))
			return (ft_mach_err_lc_lt_8(n));
		/* Checked at the command parsing level
		else if (current->cmdsize > remaining)
			return (ft_mach_err_lc_lt_sizeofcmds(n));*/
		else
		{
			//ft_mach_handle_lc
			
			/* get the next load_command */
			if (current->cmdsize > remaining)
				remaining = 0;
			else
				remaining -= current->cmdsize;
			current = (struct load_command const *)((char const *)current + 
					current->cmdsize);
		}
		n++;
	}
	return (true);
}

static t_bool	ft_mach_validate_mach_hdr(t_mach *dst, t_mapping map)
{
	dst->header = map.addr;
	//ft_mach_dump_mach_header(dst->header);
	if (!is_large_enough(map, dst->header + 1, dst->header->sizeofcmds))
		return (ft_mach_err_sizeofcmds_lt_file());
	return (true);
}

t_file	ft_mach_is_mach_o(t_mapping map)
{
	t_magic	num;

	if (is_large_enough(map, map.addr, sizeof(struct mach_header_64)))
	{
		num = *(t_magic const *)map.addr;
		if (num == MH_MAGIC)
			return (E_FILE_MACH_O);
		else if (num == MH_MAGIC_64)
			return (E_FILE_MACH_O_64);
	}
	return (E_FILE_INVALID);
}

t_bool	ft_mach_init(t_mach *dst, t_mapping map, t_file type)
{
	dst->is_64 = (type == E_FILE_MACH_O_64);
	if (!ft_mach_validate_mach_hdr(dst, map) ||
			!ft_mach_validate_lc(dst))
		return (false);
	return (true);
}
