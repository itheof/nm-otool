/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o_symtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:09:54 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/29 12:14:44 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

t_bool	ft_mach_register_symtab(t_mach *dst,
		struct symtab_command const *lc, uint32_t index)
{
	if (lc->cmdsize != sizeof(*lc))
		return (ft_mach_err_lc_size_neq_cmd(index, lc->cmd));
	dst->symtab_lc = lc;
	return (true);
}

t_bool	ft_mach_load_symtab(t_mach *dst, t_mapping map)
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
