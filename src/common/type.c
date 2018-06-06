/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:04:49 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/07 10:58:02 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <ar.h>
#include "common.h"
#include "libft/stdbool.h"
#include "libft/libc.h"

t_file	get_file_type(t_mapping map)
{
	t_file	type;

	if ((type = ft_ar_is_ar(map)) != E_FILE_INVALID)
		;
	else if ((type = ft_fat_is_fat(map)) != E_FILE_INVALID)
		;
	else if ((type = ft_mach_is_mach_o(map)) != E_FILE_INVALID)
		;
	else
		return (E_FILE_INVALID);
	return (type);
}
