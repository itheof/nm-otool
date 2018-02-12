/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/12 15:55:09 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <stdlib.h>
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
	char		*_prefix;
}				t_mapping;

t_bool	fat_get_default_arch(t_mapping map, struct fat_arch_64 **addr);

t_bool	map_file(const char *path, t_mapping *map, const char *name);
void	ft_perror(char const *name);
void	ft_puterr(char const *prefix, char const *msg);
void	unmap_file(t_mapping *map, char const *name);
void	print_path(char const *path);
t_bool	is_large_enough(t_mapping map, void *addr, size_t size);

t_bool	check_header(t_mapping map,
		struct fat_header **fat, struct mach_header_64 **mach);

#endif
