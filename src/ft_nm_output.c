/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:43:27 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 14:10:26 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft/libc.h"
#include "libft/buffer.h"

static inline t_bool	match(struct section_64 const *ptr, char const *seg,
		char const *sect)
{
	return (!ft_strncmp(ptr->sectname, sect, sizeof(ptr->sectname)) &&
			!ft_strncmp(ptr->segname, seg, sizeof(ptr->segname)));
}

static char		get_letter(t_mach *obj, uint8_t n_type, uint8_t n_sect,
		t_bool null_value)
{
	char lowercase;
	struct section_64 const *ptr;

	lowercase = (n_type & N_EXT) ? 0 : 'a' - 'A';
	if ((n_type & N_TYPE) == N_UNDF)
	{
		if (n_type & N_PEXT && !null_value)
			return ('C');
		else
			return ('U' + lowercase);
	}
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
		return ('S' + lowercase);
	}
	else if ((n_type & N_TYPE) == N_INDR)
		return ('I' + lowercase);
	return ('?');
}

void	buffer_cat_value(t_buffer *buf, size_t value, int padding, char padc)
{
	const char	arr[] = "0123456789abcdef";

	if (padding)
	{
		buffer_cat_value(buf, value >> 4, padding - 1, padc);
		if (value)
			buffer_ncat(buf, arr + (value & 0xF), 1);
		else
			buffer_ncat(buf, &padc, 1);
	}
}

void		entry_output(t_mach *obj, struct nlist_64 const *n)
{
	size_t	value;
	int		padding;
	char	letter;
	t_buffer	buf;

	padding = (obj->is_64) ? 16 : 8;
	value = (obj->is_64) ? n->n_value : ((struct nlist const *)n)->n_value;
	letter = get_letter(obj, n->n_type, n->n_sect, value == 0);
	if (n->n_un.n_strx != 0 && !(n->n_type & N_STAB) && buffer_init(&buf)) // filter debug syms
	{
		if (letter != 'U' && letter != 'u')
			buffer_cat_value(&buf, value, padding, '0');
		else
			buffer_cat_value(&buf, 0, padding, ' ');
		buffer_cat(&buf, " ");
		buffer_ncat(&buf, &letter, 1);
		buffer_cat(&buf, " ");
		buffer_cat(&buf, ft_mach_get_string_by_symbol(obj, n)); //XXX check null returns
		ft_putendl(buf.str);
		buffer_deinit(&buf);
	}
}
