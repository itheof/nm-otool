/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:43 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/26 21:08:17 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

t_bool	fat_iter(t_list *lst, t_arch_fun f, t_mapping map, t_out out)
{
	t_bool	success;

	success = true;
	while (lst && success)
	{
		out.arch_name = ((t_fat*)lst->content)->arch_name;
		success = fat_apply(lst->content, f, map, out);
		lst = lst->next;
	}
	return (success);
}

t_bool	fat_apply(t_fat *fat, t_arch_fun f, t_mapping map, t_out out)
{
	return f(map, fat->addr, out, fat->info, fat->content);
}

void	fat_deinit(t_list *lst)
{
	t_list *next;

	while (lst)
	{
		next = lst->next;
		NXFreeArchInfo(((t_fat*)lst->content)->info);
		free(lst);
		lst = next;
	}
}
