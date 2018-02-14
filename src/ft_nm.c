/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:40:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/14 12:14:44 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mach-o/fat.h>
#include "libft.h"
#include "ft_nm.h"
#include "common.h"

static t_bool	parse_opt(int *ac, char const **av[], t_opt *opt, t_env *env)
{
	int			ch;
	t_buffer	buf;

	env->name = (*av)[0];
	ft_puterr(env->name, NULL);
	OPT_INIT(*opt);
	opt->opterr = 2;
	if ((ch = ft_getopt(*ac, *av, "", opt)) != -1)
	{
		if (buffer_init_with(&buf, "usage: "))
		{
			buffer_cat(&buf, (*av)[0]);
			buffer_cat(&buf, " file...\n");
			ft_putstr_fd(buf.str, 2);
			buffer_deinit(&buf);
		}
		return (false);
	}
	*ac -= opt->optind;
	*av += opt->optind;
	return (true);
}

static t_bool	ft_nm(const char *path, t_bool show_path, t_env env)
{
	struct fat_header		*fat;
	struct mach_header_64	*mach;
	t_mapping				map;
	t_bool					success;

	success = true;
	if (map_file(path, &map, env.name))
	{
		if (check_header(map, &fat, &mach))
		{
		/*
			if (!fat_get_default_arch(map, &addr))
				return (false);
			if (addr == NULL)
			{
				while (true)
				{
					if (!fat_get_next_arch(map, &addr))
					{
						success = false;
						break;
					}
					if (addr == NULL)
						break;
					success &= process_arch(addr);
				}
				fat_get_next_arch(map, NULL);
			}
			else
				success &= process_arch(addr);*/
		}
		else
			success = false;
		ft_putchar_fd('\n', 2);
	}
	else
		success = false;
	unmap_file(&map);
	return (success);
}

int				main(int ac, char const *av[])
{
	t_env	env;
	t_opt	opt;
	t_bool	success;

	success = true;
	if (parse_opt(&ac, &av, &opt, &env) == false)
		return (1);
	if (ac == 0)
	{
		success &= ft_nm("a.out", false, env);
	}
	else if (ac > 1)
	{
		while (ac != 0)
		{
			success &= ft_nm(av[0], true, env);
			ac--;
			av++;
		}
	}
	else
		success &= ft_nm(av[0], false, env);
	ft_puterr(NULL, NULL);
	return ((success == true) ? EXIT_SUCCESS : EXIT_FAILURE);
}
