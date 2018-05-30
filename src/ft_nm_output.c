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

static inline t_bool	match(struct section_64 const *ptr, char const *seg, char const *sect)
{
	return (!ft_strncmp(ptr->sectname, sect, sizeof(ptr->sectname)) &&
			!ft_strncmp(ptr->segname, seg, sizeof(ptr->segname)));
}

static char		get_letter(t_mach *obj, uint8_t n_type, uint8_t n_sect)
{
	char lowercase;
	struct section_64 const *ptr;

	lowercase = (n_type & (N_PEXT | N_EXT)) ? 0 : 'a' - 'A';
	if ((n_type & N_TYPE) == N_UNDF)
		return ('U' + lowercase);
	else if ((n_type & N_TYPE) == N_ABS)
		return ('A' + lowercase);
	else if ((n_type & N_TYPE) == N_SECT)
	{
		if (n_sect == NO_SECT)
			return ('S' + lowercase);
		ptr = obj->sections[n_sect - 1].b64;
		if (ptr == NULL)
			return ('S' + lowercase); //TODO: error case
		if (match(ptr, SEG_TEXT, SECT_TEXT))
			return ('T' + lowercase);
		if (match(ptr, SEG_DATA, SECT_DATA))
			return ('D' + lowercase);
		if (match(ptr, SEG_DATA, SECT_BSS))
			return ('B' + lowercase);
		if (match(ptr, SEG_DATA, SECT_COMMON))
			return ('C' + lowercase);
		return ('S' + lowercase);
	}
	else if ((n_type & N_TYPE) == N_PBUD)
		return ('?'); // TODO What is this even ?
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I' + lowercase);
	else
		return (0);
	return ('?');
}

void		entry_output(t_mach *obj, struct nlist_64 const *n)
{
	if (obj->is_64)
	{
		if (n->n_un.n_strx != 0 && !(n->n_type & N_STAB)) // filter debug syms
		{
			if (n->n_value)
				printf("%.16zx %c %s\n", n->n_value,
						get_letter(obj, n->n_type, n->n_sect),
						ft_mach_get_string_by_symbol(obj, n));
			else
				printf("%16c %c %s\n", ' ',
						get_letter(obj, n->n_type, n->n_sect),
						ft_mach_get_string_by_symbol(obj, n));
		}
	}
	else
		;//TODO
}

