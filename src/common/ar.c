/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:07 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/06 12:43:39 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ar.h>
#include <mach-o/ranlib.h>
#include "libft/libc.h"
#include "libft/buffer.h"
#include "common.h"

static int	ar_get_name_length(char const *name)
{
	char const *delim;

	delim = ft_memchr(name, ' ', AR_NAME_SIZE);
	if (delim != NULL)
		return (delim - name);
	else
		return (16);
}

static t_bool	ar_err_too_small_for_header(t_mapping map, void const *addr)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (remaining size of archive too small for"
				" next archive member header at offset ");
		buffer_cat_num(&buf, map_get_offset(map, addr));
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ar_init(t_mapping map, void const *addr)
{
	struct ar_hdr const	*header;
	char				buf[AR_NAME_SIZE + 1];

	header = (struct ar_hdr const *)((char const*)addr + SARMAG);

	if (!is_large_enough(map, header, sizeof(*header)))
	{
		if (!is_eof(map, header))
			return (ar_err_too_small_for_header(map, header));
		else
		{
			// fin de l'archive
			return (true);
		}
	}
	
	snprintf(buf, ar_get_name_length(header->ar_name) + 1, "%s", header->ar_name);
	ft_putendl(buf);
}

char *ar_get_name(t_mapping map, void const *addr)
{
	return ("coucou");
}
