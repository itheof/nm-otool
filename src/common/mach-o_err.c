/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach-o_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:39:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/23 17:14:48 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

t_bool	ft_mach_err_sizeofcmds_lt_file(void)
{
	ft_puterr(NULL, OBJ_INVALID
			" (load commands extend past the end of the file)");
	return (false);
}

t_bool	ft_mach_err_lc_past_all_cmds(uint32_t index)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, OBJ_INVALID " (load command ");
		buffer_cat_num(&buf, index);
		buffer_cat(&buf,
				" extends past the end all load commands in the file)");
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
