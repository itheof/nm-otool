/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:07 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/07 19:25:17 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ar.h>
#include <mach-o/ranlib.h>
#include "libft/libc.h"
#include "libft/buffer.h"
#include "common.h"

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

//TODO: Gestion d erreur si (!ft_isdigit) ?

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
	size_t	sar_efmt1;

	sar_efmt1 = sizeof(AR_EFMT1);
	return (ar_get_numeric_value(ar_name + sar_efmt1, AR_NAME_SIZE - sar_efmt1));
}

static t_bool	ar_err_too_small_for_header(t_mapping ar, void const *addr)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (remaining size of archive too small for"
				" next archive member header at offset ");
		buffer_cat_num(&buf, map_get_offset(ar, addr));
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

static t_bool	ar_err_too_small_for_object(t_mapping ar, t_ar_obj obj)
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

static t_bool	ar_err_too_small_for_ext_name(void)
{
	return (false);
}

static t_bool	ar_parse_header(t_mapping ar, struct ar_hdr const *header,
		t_ar_obj *info)
{
	if (!is_large_enough(ar, header, sizeof(*header)))
		return (ar_err_too_small_for_header(ar, header));
	info->size = ar_header_size(header); //redundancy with info->data.size ?
	info->padding = info->size & 1;
	info->data = ar;
	info->data.size = info->size;
	info->is_ext = ft_memcmp(AR_EFMT1, header->ar_name, sizeof(AR_EFMT1)) == 0;
	if (info->is_ext)
	{
		info->name_len = ar_ext_name_length(header->ar_name);
		info->name = (const char *)(header + 1);
		if (!is_large_enough(ar, info->name, info->name_len)) // TODO: test
			return (ar_err_too_small_for_ext_name());
		info->data.addr = (const char *)info->name + info->name_len;
	}
	else
	{
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
	if (obj.is_ext)
		offset += obj.name_len;
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
	t_bool				success;
	t_ar_obj			obj;

	success = true;
	current = ((struct ar_hdr const *)((char const*)ar.addr + SARMAG));
	if (is_eof(ar, current))
		current = NULL;
	while (current != NULL)
	{
		if (!ar_parse_header(ar, current, &obj))
			return (false);
		if (!is_large_enough(ar, obj.data.addr, obj.data.size))
			return (ar_err_too_small_for_object(ar, obj));

		obj_dump(obj.data);
		current = ar_get_next_header(ar, current, obj);
	}
	return (true);
}
