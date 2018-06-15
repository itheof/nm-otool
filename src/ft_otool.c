/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:40:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 17:00:07 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include "libft/print.h"
#include "libft/libc.h"
#include "ft_otool.h"
#include "common.h"

static t_bool	ft_otool_switch_file_type(t_mapping map, t_out out, t_env env)
{
	t_file		type;
	void const	*addr;

	addr = map.addr;
	type = get_file_type(map);
	if (type == E_FILE_FAT)
		return (otool_fat_wrap(map, out, env.archs, env.all_archs));
	else if (type == E_FILE_FAT_64)
		return (otool_fat64_wrap(map, out, env.archs, env.all_archs));
	else if (type == E_FILE_AR)
		return (otool_ar_wrap(map, out, env.archs));
	else if (type == E_FILE_MACH_O)
		return (otool_mach_wrap(map, out, env.archs));
	else if (type == E_FILE_MACH_O_64)
		return (otool_mach64_wrap(map, out, env.archs));
	else
	{
		ft_puterr(NULL, ERR_INVALID);
		ft_putchar_fd('\n', 2);
		return (false);
	}
}

static t_bool	ft_otool_file_wrap(const char *path, t_env env,
		t_bool show_path)
{
	t_mapping	map;
	t_bool		success;
	t_out		out;

	if (map_file(path, &map, env.name))
	{
		ft_memset(&out, 0, sizeof(out));
		out.path = map.path;
		out.multifile = show_path;
		success = ft_otool_switch_file_type(map, out, env);
	}
	else
		success = false;
	unmap_file(&map);
	return (success);
}

int				main(int ac, char const *av[])
{
	t_env	env;
	t_bool	success;

	success = true;
	if (otool_init_env(&ac, &av, &env) == false)
		return (EXIT_FAILURE);
	if (ac == 0)
		success &= ft_otool_file_wrap("a.out", env, false);
	else if (ac > 1)
	{
		while (ac != 0)
		{
			success &= ft_otool_file_wrap(av[0], env, true);
			ac--;
			av++;
		}
	}
	else
		success &= ft_otool_file_wrap(av[0], env, false);
	arch_deinit(env.archs);
	ft_puterr(NULL, NULL);
	return ((success == true) ? EXIT_SUCCESS : EXIT_FAILURE);
}
