/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:16:04 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 16:38:03 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ar.h"

/*
** TODO: 112 (long name length characters after the #1/ are not all decimal
** numbers: 'a0' for archive member header at offset 8)
*/

t_bool	ar_err_non_digits_in_long_name(off_t offset, char const *ar_name)
{
	(void)offset;
	(void)ar_name;
	return (false);
}

t_bool	ar_err_too_small_for_header(off_t offset)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (remaining size of archive too small for"
				" next archive member header at offset ");
		buffer_cat_num(&buf, offset);
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ar_err_too_small_for_object(t_ar_obj obj)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (offset to next archive member past the "
				"end of the archive after member ");
		buffer_ncat(&buf, obj.name, obj.name_len);
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ar_err_too_small_for_ext_name(unsigned long long name_len)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (remaining size of archive too small for "
				"specified extended format name size: ");
		buffer_cat_num(&buf, name_len);
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ar_err_bad_terminator_chars(t_mapping ar, struct ar_hdr const *header,
		t_ar_obj const *info)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (terminator characters in archive member "
				"\"");
		if (info->is_ext)
			buffer_cat(&buf, " ");
		else
			buffer_ncat(&buf, header->ar_name, ar_name_length(header->ar_name));
		buffer_cat(&buf, "\" not the correct \"`\\n\" values for the "
				"archive member header at offset ");
		buffer_cat_num(&buf, map_get_offset(ar, header));
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}
