/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:43:27 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/28 17:43:51 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

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
static char		get_letter(uint8_t n_type, uint8_t n_sect)
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
	else
		return (0);
	return ('?');
}

void		entry_output(t_mach *dst, struct nlist const *a, struct nlist_64 const *b)
{
	if (dst->is_64)
	{
		if (b->n_un.n_strx != 0 && !(b->n_type & N_STAB)) // filter debug syms
		{
			if (b->n_value)
				printf("%.16zx %c %s\n", b->n_value, get_letter(b->n_type, b->n_sect), dst->strtab + b->n_un.n_strx);
			else
				printf("%16c %c %s\n", ' ', get_letter(b->n_type, b->n_sect), dst->strtab + b->n_un.n_strx);
		}
	}
	else
		;//TODO
}

