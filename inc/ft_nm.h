/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/22 16:50:38 by tvallee          ###   ########.fr       */
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
	t_bool		all_archs;
	t_list		*archs;
	size_t		narchs;

}				t_env;

t_bool	nm_fat_wrap(t_mapping map, t_out out, t_env env);

#endif
