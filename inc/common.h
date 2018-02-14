/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/14 12:25:42 by tvallee          ###   ########.fr       */
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
#  include <sys/errno.h>
#  define PERROR(x) dprintf(2, "%s: %s.\n", x, strerror(errno))
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

typedef enum	e_file
{
	E_FILE_INVALID = 0,
	E_FILE_FAT,
	E_FILE_FAT_64,
	E_FILE_AR,
	E_FILE_MACH_O,
	E_FILE_MACH_O_64,
}				t_file;

t_bool	fat_get_default_arch(t_mapping map, struct fat_arch_64 **addr);

void	ft_perror(char const *name);
void	ft_puterr(char const *prefix, char const *msg);
void	print_path(char const *path);

t_bool	map_file(const char *path, t_mapping *map, const char *name);
void	unmap_file(t_mapping *map);
t_bool	is_large_enough(t_mapping map, void *addr, size_t size);

t_file	check_header(t_mapping map,
		struct fat_header **fat, struct mach_header_64 **mach);


#endif
