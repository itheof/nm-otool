/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/07 20:27:22 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <stdlib.h>
# include "libft/stdbool.h"
# include "libft/list.h"

# ifdef NOT_CORRECTION
#  include <stdio.h>
#  include <string.h>
#  include <sys/errno.h>
#  define PERROR(x) dprintf(2, "%s: %s.\n", x, strerror(errno))
# else
#  define PERROR(x) ft_perror(x)
# endif

# define DEFAULT_ARCH (void*)((char*)NULL - 1)
# define ERR_INVALID "The file was not recognized as a valid object file"
# define AR_INVALID "truncated or malformed archive"
# define AR_NAME_SIZE sizeof(((struct ar_hdr*)(0))->ar_name)
# define AR_SIZE_SIZE sizeof(((struct ar_hdr*)(0))->ar_size)
# define SAR_EFMT1 (sizeof(AR_EFMT1) - 1) // for \0

typedef struct	s_mapping
{
	size_t		size;
	const void	*addr;
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

typedef enum	e_err
{
	E_ERR_NONE = 0,
	E_ERR_INVALID_ARCH,
	E_ERR_MALLOC,
}				t_err;

typedef struct	s_out
{
	const char	*path;
	const char	*arch_name;
	const char	*ar_name;
}				t_out;

typedef struct	s_fat
{
	void const				*addr;
	struct NXArchInfo const	*info;
}				t_fat;

typedef struct	s_ar_obj
{
	t_mapping			data;
	char const			*name;
	unsigned long long	name_len;
	unsigned long long	size;
	int					padding;
	t_bool				is_ext;
}				t_ar_obj;

typedef uint32_t	t_magic;

typedef t_bool		(*t_arch_fun)(t_mapping map, void const *addr, t_out out);

t_list	*fat_init(t_mapping map, t_bool all_archs, t_list *archs);
t_bool	fat_iter(t_list *lst, t_arch_fun f, t_mapping map, t_out out);
void	fat_deinit(t_list *lst);

t_bool	ar_iter(t_mapping ar);

void	ft_perror(char const *name);
void	ft_puterr(char const *prefix, char const *msg);
void	print_path(char const *path);
void	ft_putout(t_out out);

t_bool	map_file(const char *path, t_mapping *map, const char *name);
void	unmap_file(t_mapping *map);
t_bool	is_large_enough(t_mapping map, void const *addr, size_t size);
t_bool	is_eof(t_mapping map, void const *addr);
off_t	map_get_offset(t_mapping map, void const *addr);

t_file	get_file_type(t_mapping map, void const *addr);

t_bool	arch_add_default(t_list **dst);
t_err	arch_push_arg(t_list **lsth, char const *arg);
void	arch_deinit(t_list *archs);
t_bool	arch_fatal_err(char const *name, t_list *archs, char const *arg,
		t_err err);

#endif
