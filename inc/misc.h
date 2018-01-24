/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/04 15:49:30 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISC_H
# define MISC_H

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
	size_t		_map_size;
}				t_mapping;

t_bool	map_file(int fd, t_mapping *map);

#endif
