/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_show_symbols.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 12:54:17 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/21 17:39:25 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print.h"
#include "ft_nm.h"
#include "common.h"

#include "libft/list.h"
void	putname(t_list *elem)
{
	printf("%s\n", *(char**)elem->content);
}

t_bool	ft_nm_show_symbols(t_mapping map, t_env env)
{
	t_bool	success;
	t_file	type;

	success = true;
	printf("size %zu\n", env.narchs);
	ft_lstiter(env.archs, putname);
	if ((type = check_header(map)) != E_FILE_INVALID)
	{
		;//success = jump[type](map);
	}
	else
		success = false;
	ft_putchar_fd('\n', 2);
	return (success);
}
