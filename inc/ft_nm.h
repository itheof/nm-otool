/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/21 21:17:25 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include "common.h"
#include "libft/list.h"
#include "libft/stdbool.h"

typedef struct	s_env
{
	const char	*name;
	t_bool		show_path;
	t_bool		all_archs;
	t_list		*archs;
	size_t		narchs;

}				t_env;

t_bool	ft_nm_show_symbols(t_mapping map, t_env env);

#endif
