/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_mach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:55 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/21 16:28:10 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft/print.h"

t_bool	nm_mach_wrap(t_mapping map, t_out out, t_list *arch)
{
	t_bool	success;

	success = true;
	/*
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
	*/
	return (true);
}

t_bool	nm_mach64_wrap(t_mapping map, t_out out, t_list *arch)
{
	t_bool	success;
	t_mach	current;

	success = true;
	if (!ft_mach_init(&current, map, E_FILE_MACH_O_64))
		return (false);
	return (true);
}
