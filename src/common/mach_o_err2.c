/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o_err2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:32:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 16:33:18 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

t_bool	ft_mach_err_symtab_not_aligned(void)
{
	ft_puterr(NULL, OBJ_INVALID
			" (symtab not aligned on a pointer size boundary)");
	return (false);
}

t_bool	ft_mach_err_symtab_gt_file(void)
{
	ft_puterr(NULL, OBJ_INVALID
			" (symtab extends past the end of the file)");
	return (false);
}

t_bool	ft_mach_err_strtab_gt_file(void)
{
	ft_puterr(NULL, OBJ_INVALID
			" (strtab extends past the end of the file)");
	return (false);
}

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
