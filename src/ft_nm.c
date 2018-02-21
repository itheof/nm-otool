/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:40:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/21 17:20:16 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include "libft/buffer.h"
#include "libft/print.h"
#include "libft/libc.h"
#include "ft_nm.h"
#include "common.h"

static t_bool	usage_and_arch_deinit(char const *name, char option,
		t_list *archs)
{
	t_buffer	buf;
	char		tmp[2];

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, name);
		buffer_cat(&buf, ": Unknown command line argument '");
		tmp[1] = 0;
		tmp[0] = option;
		buffer_cat(&buf, tmp);
		buffer_cat(&buf, "'.\n");
		ft_putstr_fd(buf.str, 2);
		buffer_deinit(&buf);
	}
	arch_deinit(archs);
	if (buffer_init(&buf))
	{
		buffer_cat(&buf, "Usage: ");
		buffer_cat(&buf, name);
		buffer_cat(&buf, " [-arch arch_type] file...\n");
		ft_putstr_fd(buf.str, 2);
		buffer_deinit(&buf);
	}
	return (false);
}

static t_bool	parse_opt(int *ac, char const **av[], t_env *env)
{
	int		i;
	t_err	err;

	env->name = (*av)[0];
	env->archs = NULL;
	env->narchs = 0;
	i = 1;
	while (i < *ac)
	{	
		if (ft_strcmp((*av)[i], "--") == 0)
		{
			i++;
			break;
		}
		else if (ft_strcmp("-arch", (*av)[i]) == 0 && i < *ac + 1)
		{
			if ((err = arch_push_arg(
							&(env->archs), (*av)[i + 1], &(env->narchs))) &&
					arch_fatal_err(env->name, env->archs, (*av)[i + 1], err))
				return (false);
			i += 2;
		}
		else if (ft_strlen((*av)[i]) > 1 && (*av)[i][0] == '-')
			return (usage_and_arch_deinit(env->name, (*av)[i][1], env->archs));
		else
			break;
	}
	ft_puterr(env->name, NULL);
	*ac -= i;
	*av += i;
	env->show_path = (*ac > 1) ? true : false;
	return (true);
}

static t_bool	ft_nm(const char *path, t_env env)
{
	t_mapping	map;
	t_bool		success;

	if (map_file(path, &map, env.name))
		success = ft_nm_show_symbols(map, env);
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
	if (parse_opt(&ac, &av, &env) == false)
		return (1);
	if (ac == 0)
		success &= ft_nm("a.out", env);
	else if (ac > 1)
	{
		while (ac != 0)
		{
			success &= ft_nm(av[0], env);
			ac--;
			av++;
		}
	}
	else
		success &= ft_nm(av[0], env);
	ft_puterr(NULL, NULL);
	return ((success == true) ? EXIT_SUCCESS : EXIT_FAILURE);
}
