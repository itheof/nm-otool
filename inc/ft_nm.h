/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 16:35:59 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

t_bool			nm_fat_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs);
t_bool			nm_fat64_wrap(t_mapping map, t_out out, t_list *arch,
		t_bool all_archs);
t_bool			nm_ar_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			nm_mach_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			nm_mach64_wrap(t_mapping map, t_out out, t_list *arch);
t_bool			nm_init_env(int *ac, char const **av[], t_env *env);
void			entry_output(t_mach *obj, struct nlist_64 const *n);

#endif
