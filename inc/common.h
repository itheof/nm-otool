/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:11:56 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 18:12:06 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <mach-o/fat.h>
# include <mach-o/arch.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <stdlib.h>
# include <sys/types.h>
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
# define MAX_SEGMENTS 10
# define MAX_FAT_ARCH 16

typedef struct					s_mapping
{
	size_t		size;
	const void	*addr;
	const char	*path;
	t_bool		mallocd;
}								t_mapping;

typedef enum					e_file
{
	E_FILE_INVALID = 0,
	E_FILE_FAT,
	E_FILE_FAT_64,
	E_FILE_AR,
	E_FILE_MACH_O,
	E_FILE_MACH_O_64,
}								t_file;

typedef enum					e_err
{
	E_ERR_NONE = 0,
	E_ERR_INVALID_ARCH,
	E_ERR_MALLOC,
}								t_err;

typedef struct					s_out
{
	const char					*path;
	const char					*arch_name;
	const char					*ar_name;
	t_bool						multifile;
}								t_out;

typedef struct					s_fat
{
	t_bool						is_64;
	struct fat_arch_64			arr[MAX_FAT_ARCH];
	uint32_t					narchs;
	t_bool						all_archs;
	t_list						*arch;
}								t_fat;

typedef struct					s_ar_obj
{
	t_mapping					data;
	char const					*name;
	unsigned long long			name_len;
	unsigned long long			size;
	int							padding;
	t_bool						is_ext;
}								t_ar_obj;

typedef struct					s_mach
{
	t_bool						is_64;
	union						u_headers
	{
		struct mach_header_64 const	*b64;
		struct mach_header const	*b32;
	}							header;
	struct load_command	const	*lc_start;
	struct symtab_command const	*symtab_lc;

	char const					*strtab;
	union						u_nlists {
		struct nlist const		*b32;
		struct nlist_64 const	*b64;
	}							symtab;

/*
** v: 0 indexed unlike sections indexes
*/

	union						u_sections {
		struct section const	*b32;
		struct section_64 const	*b64;
	}							sections[MAX_SECT];
}								t_mach;

typedef uint32_t				t_magic;

typedef t_bool					(*t_arch_fun)(t_mapping map, t_out out,
		t_list *arch);

/*
** FAT
*/

t_bool							fat_init(t_mapping map, t_fat *obj);
t_bool							fat_iter(t_fat *obj, t_arch_fun f,
		t_mapping map, t_out out);
void							fat_deinit(t_list *lst);
t_file							ft_fat_is_fat(t_mapping map);

/*
** AR
*/

t_bool							ar_iter(t_mapping ar, t_out out, t_list *arch,
		t_arch_fun f);
t_file							ft_ar_is_ar(t_mapping map);

/*
** Mach-O
*/

t_bool							ft_mach_init(t_mach *dst, t_mapping map,
		t_file type);
t_file							ft_mach_is_mach_o(t_mapping map);
char const						*ft_mach_get_string_by_symbol(t_mach *dst,
		struct nlist_64 const *n);

/*
** debug
*/

void							ft_perror(char const *name);
void							ft_puterr(char const *prefix, char const *msg);
void							print_path(char const *path);
t_bool							ft_perror_return_false(char const *str);
void							ft_putout(t_out out);
t_bool							ft_match_arch(t_mach *target, NXArchInfo *req);

t_bool							map_file(const char *path, t_mapping *map,
		const char *name);
void							unmap_file(t_mapping *map);
t_bool							is_large_enough(t_mapping map, void const *addr,
		size_t size);
t_bool							is_eof(t_mapping map, void const *addr);
off_t							map_get_offset(t_mapping map, void const *addr);

t_file							get_file_type(t_mapping map);

t_bool							arch_add_default(t_list **dst);
t_err							arch_push_arg(t_list **lsth, char const *arg);
t_bool							arch_deinit(t_list *archs);
t_bool							arch_fatal_err(char const *name, t_list *archs,
		char const *arg, t_err err);

#endif
