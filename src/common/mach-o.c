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

static void		ft_mach_lc_dump(struct load_command const *lc, uint32_t max_len)
{
	size_t	len;

	if (lc->cmdsize <= max_len)
		len = lc->cmdsize;
	else
		return ; // this is a corrupt object
	ft_hexdump((const char *)lc, len);
}

static t_bool	ft_mach_register_symtab(t_mach *dst,
		struct symtab_command const *lc)
{
	dst->symtab_lc = lc;
	return (true);
}

static t_bool	ft_mach_check_lc_size(struct load_command const *lc,
		uint32_t max_len)
{
	if (lc->cmdsize > max_len)
	{
		OBJ_ERROR("Malformed MachO file.")
		return (false);
	}
	else
		return (true);
}

static t_bool	ft_mach_switch_lc(t_mach *dst, struct load_command const *lc,
		uint32_t max_len)
{
	if (lc->cmd == LC_SYMTAB)
		return (ft_mach_check_lc_size(lc, max_len) &&
			ft_mach_register_symtab(dst, (struct symtab_command const *)lc));
	else
		return (true);
}

static t_bool	ft_mach_register_lc(t_mach *dst)
{
	uint32_t					remaining;
	uint32_t					n;
	struct load_command const	*current;

	if (dst->is_64)
		dst->lc_start = (struct load_command const *)(dst->header + 1);
	else
		dst->lc_start = (struct load_command const *)(
				(char const *)dst->header - sizeof(struct mach_header));
	dst->symtab_lc = NULL;

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
			if (!ft_mach_switch_lc(dst, current, remaining))
				return (false);

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

/*
       U (undefined),
	   A (absolute),
	   T (text section symbol),
	   D (data section symbol),
	   B (bss section symbol),
	   C (common symbol),
	   S (symbol in a section other than those above)
	   I (indirect symbol)
       (non-external),  the  symbol's  type  is instead represented by the corresponding lowercase letter.  A lower case u in a dynamic shared library indicates a
       undefined reference to a private external in another module in the same library.
*/

static char		stab_get_letter(t_mach *dst, uint8_t n_type, uint8_t n_sect)
{
	char lowercase;

	lowercase = (n_type & (N_PEXT | N_EXT)) ? 0 : 'a' - 'A';
	if ((n_type & N_TYPE) == N_UNDF)
		return ('U' + lowercase);
	else if ((n_type & N_TYPE) == N_ABS)
		return ('A' + lowercase);
	else if ((n_type & N_TYPE) == N_SECT)
	{
		if (n_sect == NO_SECT)
			return ('S');
		
	}
	else if ((n_type & N_TYPE) == N_PBUD)
		return ('?'); // TODO What is this even ?
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I');
}

static void		entry_output(t_mach *dst, struct nlist const *a,struct nlist_64 const *b)
{
	if (dst->is_64)
	{
		if (b->n_un.n_strx != 0 && !(b->n_type & N_STAB)) // filter debug syms
		{
			if (b->n_value)
				printf("%.16zx %c %s\n", (void*)b->n_value, stab_get_letter(b->n_type), dst->strtab + b->n_un.n_strx);
			else
				printf("%16c %c %s\n", ' ', stab_get_letter(b->n_type), dst->strtab + b->n_un.n_strx);
		}
	}
	else
		;//TODO
}

static t_bool	ft_mach_load_symtab(t_mach *dst, t_mapping map)
{
	size_t	symsize;
	size_t	nlistsize;

	if (dst->is_64)
		nlistsize = sizeof(*dst->symtab.b64);
	else
		nlistsize = sizeof(*dst->symtab.b32);
	symsize = dst->symtab_lc->nsyms * nlistsize;
	/* test map.addr overflow, bad offset and so on*/
	if (!is_large_enough(map, (char const *)map.addr + dst->symtab_lc->symoff,
				symsize))
		return (false /* plus error message*/);
	dst->symtab.b64 = (void *)((char const *)map.addr + dst->symtab_lc->symoff);
	/* check alignement ^ */

	if (!is_large_enough(map, (char const *)map.addr + dst->symtab_lc->stroff,
				dst->symtab_lc->strsize))
		return (false /* plus error message */);
	dst->strtab = (char const *)map.addr + dst->symtab_lc->stroff;

	for (int i = 0; i < dst->symtab_lc->nsyms; i++)
	{
		entry_output(dst, dst->symtab.b32 + i, dst->symtab.b64 + i);
	}
	return (true);
}

static t_bool	ft_mach_load(t_mach *dst, t_mapping map)
{
	/* load symtable */
	if (dst->symtab_lc != NULL && !ft_mach_load_symtab(dst, map))
		return (false);
	else
		;/* exec other load cmds */
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
	if (!ft_mach_register_mach_hdr(dst, map))
		return (false);
	dst->is_64 = (type == E_FILE_MACH_O_64);
	if (!ft_mach_register_lc(dst))
		return (false);
	if (!ft_mach_load(dst, map))
		return (false);
	return (true);
}
