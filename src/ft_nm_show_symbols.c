/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_show_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:54:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/21 13:10:35 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "common.h"

t_bool	ft_nm_show_symbols(t_mapping map, t_env env)
{
	t_bool	success;
	t_file	type;

	success = true;
	if ((type = check_header(map)) != E_FILE_INVALID)
	{
		;//success = jump[type](map);
	}
	else
		success = false;
	ft_putchar_fd('\n', 2);
	return (success);
}
