/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 16:35:59 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_otool_H
# define FT_otool_H

# include "common.h"
# include "libft/list.h"
# include "libft/stdbool.h"

typedef struct	s_env
{
	const char	*name;
	t_bool		all_archs;
	t_list		*archs;
	t_bool		default_arch;
}				t_env;

t_bool			otool_fat_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs);
t_bool			otool_fat64_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs);
t_bool			otool_ar_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			otool_mach_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			otool_mach64_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			otool_init_env(int *ac, char const **av[], t_env *env);

#endif
