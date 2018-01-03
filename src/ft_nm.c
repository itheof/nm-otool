/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:40:34 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/02 22:16:39 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_nm.h"

static void		usage(const char *name)
{
   ft_putstr_fd("usage: ", 2);
   ft_putstr_fd(name, 2);
   ft_putendl_fd(" [-APv] [-efox] [-g|-u] [-t format] file...", 2);
}


static t_bool	parse_opt(int ac, char const *av[], t_opt *opt, t_env *env)
{
	int		ch;

	OPT_INIT(*opt);
	opt->opterr = 2;
	while ((ch = ft_getopt(ac, av, "APvefoxgut:", opt)) != -1)
	{
		if (ft_strchr("APvefoxgut", ch))
		{
			ft_putchar(ch);
			ft_putchar(' ');
			if (ch == 't')
				ft_putendl(opt->optarg);
			else
				ft_putchar(10);
		}
		else
		{
			usage(av[0]);
			return (false);
		}
	}
	return (true);
}

static t_bool	ft_nm(const char *name, t_bool show_file)
{
	ft_putendl(name);
	return (true);
}

int						main(int ac, char const *av[])
{
	t_opt	opt;
	t_env	env;
	t_bool	success;

	success = true;
	if (parse_opt(ac, av, &opt, &env) == false)
		return (1);
	ac -= opt.optind;
	av += opt.optind;
	if (ac == 0)
	{
		success &= ft_nm("a.out", false);
	}
	else if (ac > 1)
	{
		while (ac != 0)
		{
			success &= ft_nm(av[0], true);
			ac--;
			av++;
		}
	}
	else
		success &= ft_nm(av[0], false);
	return ((success) ? 0 : 1);
}
