/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:07 by tvallee           #+#    #+#             */
/*   Updated: 2018/04/26 10:46:17 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ar.h"

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

//TODO: overflow unsigned long long -> size_t ?
static size_t	ar_ext_name_length(char const *ar_name)
{
	return (ar_get_numeric_value(ar_name + SAR_EFMT1, AR_NAME_SIZE - SAR_EFMT1));
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

	current = ((struct ar_hdr const *)((char const*)ar.addr + SARMAG));
	if (is_eof(ar, current))
		current = NULL;
	while (current != NULL)
	{
		if (!ar_parse_header(ar, current, &obj))
			return (false);
		if (!is_large_enough(ar, current + 1, obj.size + obj.padding))
			return (ar_err_too_small_for_object(obj));

		obj_dump(obj.data);
		current = ar_get_next_header(ar, current, obj);
	}
	return (true);
}
