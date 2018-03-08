/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:07 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/08 17:57:53 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ar.h>
#include <mach-o/ranlib.h>
#include "libft/libc.h"
#include "libft/buffer.h"
#include "common.h"

//TODO: Split into several files

static unsigned long long	ar_get_numeric_value(char const *str, size_t n)
{
	unsigned long long	ret;
	size_t				i;

	ret = 0;
	i = 0;
	while (ft_isdigit(str[i]) && i < n)
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	return (ret);
}

//TODO: Gestion d erreur si (!ft_isdigit)

static unsigned long long	ar_header_size(struct ar_hdr const *header)
{
	return (ar_get_numeric_value(header->ar_size, AR_SIZE_SIZE));
}

static size_t	ar_name_length(char const *name)
{
	char const *delim;

	delim = ft_memchr(name, ' ', AR_NAME_SIZE);
	if (delim != NULL)
		return (delim - name);
	else
		return (AR_NAME_SIZE);
}

//TODO: overflow unsigned long long -> size_t ?
static size_t	ar_ext_name_length(char const *ar_name)
{
	return (ar_get_numeric_value(ar_name + SAR_EFMT1, AR_NAME_SIZE - SAR_EFMT1));
}

static t_bool	ar_err_non_digits_in_size()
{
//TODO: 111 (characters in size field in archive header are not all decimal numbers: 'a' for archive member header at offset 8)
	return (false);
}

static t_bool	ar_err_non_digits_in_long_name(off_t offset,
		char const *ar_name)
{
//TODO: 112 (long name length characters after the #1/ are not all decimal numbers: 'a0' for archive member header at offset 8)
	return (false);
}

static t_bool	ar_err_too_small_for_header(off_t offset)
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

static t_bool	ar_err_too_small_for_object(t_ar_obj obj)
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

static t_bool	ar_err_too_small_for_ext_name(unsigned long long name_len)
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

static t_bool	ar_err_bad_terminator_chars(t_mapping ar,
		struct ar_hdr const *header, t_ar_obj const *info)
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

static t_bool	ar_parse_header(t_mapping ar, struct ar_hdr const *header,
		t_ar_obj *info)
{
	if (!is_large_enough(ar, header, sizeof(*header)))
		return (ar_err_too_small_for_header(map_get_offset(ar, header)));
	info->size = ar_header_size(header);
	info->padding = info->size & 1;
	info->data = ar;
	info->is_ext = ft_memcmp(AR_EFMT1, header->ar_name, SAR_EFMT1) == 0;
	if (ft_memcmp(header->ar_fmag, ARFMAG, SARFMAG) != 0)
		return (ar_err_bad_terminator_chars(ar, header, info));
	if (info->is_ext)
	{
		info->name_len = ar_ext_name_length(header->ar_name);
		info->data.size = info->size - info->name_len;
		info->name = (const char *)(header + 1);
		if (!is_large_enough(ar, info->name, info->name_len))
			return (ar_err_too_small_for_ext_name(info->name_len));
		info->data.addr = (const char *)info->name + info->name_len;
	}
	else
	{
		info->data.size = info->size;
		info->name = header->ar_name;
		info->name_len = ar_name_length(info->name);
		info->data.addr = (const char *)(header + 1);
	}
	return (true);
}

static struct ar_hdr const	*ar_get_next_header(t_mapping ar,
		struct ar_hdr const *last, t_ar_obj obj)
{
	struct ar_hdr const	*next;
	unsigned long long	offset;

	offset = obj.size + obj.padding;
	next = (struct ar_hdr const *)((char const *)(last + 1) + offset);
	return ((is_eof(ar, next)) ? NULL : next);
}

static void	obj_dump(t_mapping obj)
{
	if (obj.size > 0)
		ft_hexdump(obj.addr, obj.size);
}

t_bool	ar_iter(t_mapping ar)
{
	struct ar_hdr const	*current;
	t_ar_obj			obj;

	setbuf(stderr, NULL);
	current = ((struct ar_hdr const *)((char const*)ar.addr + SARMAG));
	if (is_eof(ar, current))
		current = NULL;
	while (current != NULL)
	{
		if (!ar_parse_header(ar, current, &obj))
			return (false);
		if (!is_large_enough(ar, current + 1, obj.size + obj.padding))
			return (ar_err_too_small_for_object(obj));

		dprintf(2, "size: %llu, %.*s:\n", obj.data.size, obj.name_len, obj.name);
		obj_dump(obj.data);
		current = ar_get_next_header(ar, current, obj);
	}
	return (true);
}
