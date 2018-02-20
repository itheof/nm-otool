/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 19:48:48 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/20 11:48:21 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

#include "libft/list.h"
#include "libft/stdbool.h"

typedef struct	s_env
{
	const char	*name;
	t_bool		show_path;
	t_list		*archs;
}				t_env;

#endif
