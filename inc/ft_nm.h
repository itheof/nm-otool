/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/06 12:30:27 by tvallee          ###   ########.fr       */
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
}				t_env;

t_bool	nm_fat_wrap(t_mapping map, t_out out, t_env env);
t_bool	nm_fat64_wrap(t_mapping map, t_out out, t_env env);
t_bool	nm_ar_wrap(t_mapping map, t_out out, t_list *arch);
t_bool	nm_mach_wrap(t_mapping map, t_out out, t_list *arch);
t_bool	nm_mach64_wrap(t_mapping map, t_out out, t_list *arch);
t_bool	nm_init_env(int *ac, char const **av[], t_env *env);

#endif
