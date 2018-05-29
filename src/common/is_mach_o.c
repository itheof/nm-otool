/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mach_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:48:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/28 15:49:15 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

t_file	ft_mach_is_mach_o(t_mapping map)
{
	t_magic	num;

	if (is_large_enough(map, map.addr, sizeof(struct mach_header_64)))
	{
		num = *(t_magic const *)map.addr;
		if (num == MH_MAGIC)
			return (E_FILE_MACH_O);
		else if (num == MH_MAGIC_64)
			return (E_FILE_MACH_O_64);
	}
	return (E_FILE_INVALID);
}
