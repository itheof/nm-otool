/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o_symtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:09:54 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 15:08:14 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

t_bool		ft_mach_register_symtab(t_mach *dst,
		struct symtab_command const *lc, uint32_t index)
{
	if (lc->cmdsize != sizeof(*lc))
		return (ft_mach_err_lc_size_neq_cmd(index, lc->cmd));
	dst->symtab_lc = lc;
	return (true);
}

/*
** v returns "" if not enough space
*/

char const	*ft_mach_get_string_by_symbol(t_mach *dst, struct nlist_64 const *n)
{
	char const	*ret;
	char const	*delim;

	if (n->n_un.n_strx > dst->symtab_lc->strsize)
		return ("");
	ret = dst->strtab + n->n_un.n_strx;
	if (ret < dst->strtab)
		return ("");
	delim = dst->strtab + dst->symtab_lc->strsize;
	while (delim != dst->strtab)
	{
		if (!*delim)
			return (ret);
		delim--;
	}
	return ("");
}

/*
** ln38: make sure the string table is null terminated
*/

t_bool		ft_mach_load_symtab(t_mach *dst, t_mapping map)
{
	size_t	symsize;
	size_t	nlistsize;

	if (dst->is_64)
		nlistsize = sizeof(*dst->symtab.b64);
	else
		nlistsize = sizeof(*dst->symtab.b32);
	symsize = dst->symtab_lc->nsyms * nlistsize;
	if (!is_large_enough(map, (char const *)map.addr + dst->symtab_lc->symoff,
				symsize))
		return (ft_mach_err_symtab_gt_file());
	dst->symtab.b64 = (void *)((char const *)map.addr + dst->symtab_lc->symoff);
	if (!is_large_enough(map, (char const *)map.addr + dst->symtab_lc->stroff,
				dst->symtab_lc->strsize))
		return (ft_mach_err_strtab_gt_file());
	dst->strtab = (char const *)map.addr + dst->symtab_lc->stroff;
	return (true);
}
