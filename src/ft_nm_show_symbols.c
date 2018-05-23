/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_show_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:54:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/21 16:17:27 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print.h"
#include "ft_nm.h"
#include "common.h"
#include "libft/list.h"

t_bool	nm_ar_wrap(t_mapping map, t_out out, t_list *arch)
{
	if (!ar_iter(map))
		return (false);
	/*
	(char*)addr += SARMAG;
		out.path = map.path;
		if ((out.ar_name = ar_get_name(map, addr)) == NULL)
		{
			ft_puterr(NULL, AR_INVALID);
			return (false);
		}

		printf("%s\n", out.ar_name);
		free((char*)out.ar_name);
		*/
	return (true);
}

t_bool	nm_fat_wrap(t_mapping map, t_out out, t_env env)
{
	//t_file	type;
	//t_list	*lst;
	t_bool	success;

	success = true;
		/*
		if ((lst = fat_init(map, env.all_archs, env.archs)) == NULL)
			success = false;
		else
		{
			if (lst->next != NULL) // aka len > 1
				success = fat_iter(lst, nm_ar_wrap, map, out);
			else
				success = nm_ar_wrap(map, ((fat*)lst->content)->addr,
						out, lst);
			fat_deinit(lst);
		}
		if (!success)
			ft_putchar_fd(10, 2);
		return (success);
		*/
	printf("nm_fat_wrap\n");
	return (false);
}

t_bool	nm_fat64_wrap(t_mapping map, t_out out, t_env env)
{
	t_bool	success;

	success = true;

	printf("nm_fat64_wrap\n");
	return (success);
}
