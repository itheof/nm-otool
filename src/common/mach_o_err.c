/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach-o_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:39:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 16:33:59 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

static char	const	*g_cmd_lookup[BIGGEST_CMD_NUM] = {
	[LC_SYMTAB] = "LC_SYMTAB",
	[LC_SEGMENT] = "LC_SEGMENT",
	[LC_SEGMENT_64] = "LC_SEGMENT_64"
};

t_bool	ft_mach_err_lc_size_lt_cmd(uint32_t index, uint32_t cmd)
{
	t_buffer			buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, OBJ_INVALID " (load command ");
		buffer_cat_num(&buf, index);
		buffer_cat(&buf, " ");
		buffer_cat(&buf, g_cmd_lookup[cmd]);
		buffer_cat(&buf,
				" cmdsize too small)");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ft_mach_err_lc_size_neq_cmd(uint32_t index, uint32_t cmd)
{
	t_buffer			buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, OBJ_INVALID " (");
		buffer_cat(&buf, g_cmd_lookup[cmd]);
		buffer_cat(&buf, " command ");
		buffer_cat_num(&buf, index);
		buffer_cat(&buf, " has incorrect cmdsize)");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ft_mach_err_lc_size_not_aligned(uint32_t index)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, OBJ_INVALID " (load command ");
		buffer_cat_num(&buf, index);
		buffer_cat(&buf,
				" cmdsize not a multiple of 8)");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

t_bool	ft_mach_err_lc_lt_8(uint32_t index)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, OBJ_INVALID " (load command ");
		buffer_cat_num(&buf, index);
		buffer_cat(&buf,
				" with size less than 8 bytes)");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}
