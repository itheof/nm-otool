/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_show_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:54:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/26 20:40:26 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print.h"
#include "ft_nm.h"
#include "common.h"
#include "libft/list.h"

t_bool	nm_err_invalid_file(t_mapping map)
{
	ft_puterr(NULL, ERR_INVALID);
	return (false);
}

t_bool	nm_mach_wrap(t_mapping map, void const *addr, t_out out,
		NXArchInfo *info)
{
	t_bool	success;
	t_file	type;

	success = true;
	if ((type = get_file_type(map, map.addr)) == E_FILE_MACH_O)
	{

	}
	else if ((type = get_file_type(map, map.addr)) == E_FILE_MACH_O_64)
	{

	}
	else
	{
		return (false);
	}
}

t_bool	nm_ar_wrap(t_mapping map, void const *addr, t_out out, NXArchInfo *info)
{
	t_bool	success;
	t_file	type;

	out.ar_name = NULL;
	success = true;
	if ((type = get_file_type(map, map.addr)) == E_FILE_AR)
	{
		out.path = map.path;
		out.ar_name = "";
	}
	else if (type == E_FILE_MACH_O || type == E_FILE_MACH_O_64)
		success = nm_mach_wrap(map, addr, out, info);
	else
	{
		ft_puterr(NULL, ERR_INVALID);
		ft_putchar_fd(10, 2);
		success = false;
	}
	return (success);
}

t_bool	nm_fat_wrap(t_mapping map, t_out out, t_env env)
{
	t_file	type;
	t_list	*lst;
	t_bool	success;

	out.arch_name = NULL;
	success = true;
	if ((type = get_file_type(map, map.addr)) == E_FILE_FAT)
	{
		if ((lst = fat_init(map, env.all_archs, env.archs)) == NULL)
			success = false;
		else
		{
			if (ft_lstlen(lst) > 1)
				success = fat_iter(lst, nm_ar_wrap, map, out);
			else
				success = fat_apply(lst->content, nm_ar_wrap, map, out);
			fat_deinit(lst);
		}
		if (!success)
			ft_putchar_fd(10, 2);
		return (success);
	}
	else if (type == E_FILE_FAT_64)
	{
		// copy above and change to 64
		return (success);
	}
	else
		return (nm_ar_wrap(map, map.addr, out, NULL));
}
