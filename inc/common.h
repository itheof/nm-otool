/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/29 16:49:13 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft/stdbool.h"

# ifdef NOT_CORRECTION
#  include <stdio.h>
#  define PERROR(x) perror(x)
# else
#  define PERROR(x) ft_perror(x)
# endif

typedef struct	s_mapping
{
	size_t		size;
	void		*addr;
	const char	*path;
	t_bool		_mallocd;
}				t_mapping;

t_bool	map_file(const char *path, t_mapping *map, const char *name);
void	ft_perror(char const *name);
void	unmap_file(t_mapping *map);
void	print_path(char const *path);

#endif
