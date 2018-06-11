/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 17:50:40 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

/*
t_bool	fat_iter(t_list *lst, t_arch_fun f, t_mapping map, t_out out)
{
	t_bool	success;

	success = true;
	while (lst && success)
	{
		out.arch_name = ((t_fat*)lst->content)->arch_name;
		success = f(map, ((t_fat*)lst->content)->addr, out,
				((t_fat*)lst->content)->info);
		lst = lst->next;
	}
	return (success);
}

void	fat_deinit(t_list *lst)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		if (((t_fat*)lst->content)->info != NULL)
			NXFreeArchInfo(((t_fat*)lst->content)->info);
		free(lst);
		lst = next;
	}
}
*/

t_file	ft_fat_is_fat(t_mapping map)
{
	if (is_large_enough(map, map.addr, sizeof(t_magic)) &&
			(*(t_magic*)map.addr == FAT_CIGAM ||
			*(t_magic*)map.addr == FAT_CIGAM_64))
		return (true);
	return (E_FILE_INVALID);
}
