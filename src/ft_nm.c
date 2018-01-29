/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:40:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/29 14:37:32 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"
#include "common.h"

static t_bool	parse_opt(int ac, char const *av[], t_opt *opt, t_env *env)
{
	int		ch;

	env->name = av[0];
	OPT_INIT(*opt);
	opt->opterr = 2;
	if ((ch = ft_getopt(ac, av, "", opt)) != -1)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putendl_fd(" file...", 2);
		return (false);
	}
	return (true);
}

static t_bool	ft_nm(const char *path, t_bool show_path, t_env env)
{
	t_mapping map;

	if (!map_file(path, &map, env.name))
		return (false);
	ft_putendl(path);
	unmap_file(map);
	return (true);
}

int						main(int ac, char const *av[])
{
	t_env	env;
	t_opt	opt;
	t_bool	success;

	success = true;
	if (parse_opt(ac, av, &opt, &env) == false)
		return (1);
	ac -= opt.optind;
	av += opt.optind;
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
	return ((success == true) ? EXIT_SUCCESS : EXIT_FAILURE);
}
