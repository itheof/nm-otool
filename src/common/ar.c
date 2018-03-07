/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:41:07 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/07 13:49:09 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ar.h>
#include <mach-o/ranlib.h>
#include "libft/libc.h"
#include "libft/buffer.h"
#include "common.h"

static unsigned long long	ar_get_member_size(struct ar_hdr const *header)
{
	unsigned long long	ret;
	size_t				i;

	ret = 0;
	i = 0;
	while (ft_isdigit(header->ar_size[i]) && i < AR_SIZE_SIZE)
	{
		ret *= 10;
		ret += header->ar_size[i] - '0';
		i++;
	}
	return (ret);
}

static int	ar_get_name_length(char const *name)
{
	char const *delim;

	delim = ft_memchr(name, ' ', AR_NAME_SIZE);
	if (delim != NULL)
		return (delim - name);
	else
		return (16);
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

static t_bool	ar_err_too_small_for_object(t_mapping ar,
		struct ar_hdr const *header)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, AR_INVALID " (offset to next archive member past the "
				"end of the archive after member ");
		buffer_ncat(&buf, header->ar_name,
				ar_get_name_length(header->ar_name));
		buffer_cat(&buf, ")");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

static t_bool	ar_check_member(t_mapping ar, struct ar_hdr const *header)
{
	if (!is_large_enough(ar, header, sizeof(*header)))
		return (ar_err_too_small_for_header(ar, header));
	if (!is_large_enough(ar, header + 1, ar_get_member_size(header)))
		return (ar_err_too_small_for_object(ar, header));
	return (true);
}

static struct ar_hdr const	*ar_get_next_member(t_mapping ar,
		struct ar_hdr const *last)
{
	struct ar_hdr const	*next;

	if (last == NULL)
		next = ((struct ar_hdr const *)((char const*)ar.addr + SARMAG));
	else
		next = (struct ar_hdr const *)(
				(char const *)(last + 1) + ar_get_member_size(last));
	return ((is_eof(ar, next)) ? NULL : next);
}

t_bool	ar_iter(t_mapping ar)
{
	struct ar_hdr const	*current;
	t_bool				success;
	char				buf[AR_NAME_SIZE + 1];

	current = NULL;
	success = true;
	while ((current = ar_get_next_member(ar, current)) != NULL)
	{
		if (!ar_check_member(ar, current))
			return (false);
		snprintf(buf, ar_get_name_length(current->ar_name) + 1, "%s",
				current->ar_name);
		ft_putendl(buf);
	}


	if (success)
	{
		;// success cleanup
	}
	else
	{
		;// !success cleanup
	}
	return (success);
}
