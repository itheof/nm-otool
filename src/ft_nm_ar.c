/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_ar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 11:41:52 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 13:34:20 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool	nm_test(t_mapping map, t_out out, t_list *arch)
{
	t_file	type;

	type = get_file_type(map);
	if (type == E_FILE_MACH_O)
		return (nm_mach_wrap(map, out, arch));
	else if (type == E_FILE_MACH_O_64)
		return (nm_mach64_wrap(map, out, arch));
	return (true);
}

t_bool			nm_ar_wrap(t_mapping map, t_out out, t_list *arch)
{
	return (ar_iter(map, out, arch, &nm_test));
}
