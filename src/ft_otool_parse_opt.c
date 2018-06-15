/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_parse_opt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:45:52 by tvallee           #+#    #+#             */
/*   Updated: 2018/03/05 18:30:29 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/buffer.h"
#include "libft/libc.h"
#include "libft/print.h"
#include "ft_otool.h"

static t_bool	usage(char const *name, char option)
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

static t_bool	is_opt(char const *arg)
{
	return (arg && ft_strlen(arg) > 1 && arg[0] == '-');
}

static t_bool	otool_init_env_end(t_env *env, int *ac, char const **av[],
		int i)
{
	ft_puterr(env->name, NULL);
	if (env->default_arch)
	{
		if ((env->archs = ft_lstnewcopy(DEFAULT_ARCH, sizeof(void*))) == NULL)
		{
			ft_puterr(NULL, "malloc failed");
			ft_puterr(NULL, NULL);
			return (false);
		}
	}
	*ac -= i;
	*av += i;
	return (true);
}

static t_bool	process_arch_arg(t_env *env, int *ac, char const **av[], int *i)
{
	t_err		err;
	t_buffer	buf;

	if (ft_strcmp("-arch", (*av)[*i]))
		return (true);
	if (*i + 1 >= *ac)
	{
		if (buffer_init(&buf))
		{
			buffer_cat(&buf, (*av)[0]);
			buffer_cat(&buf, ": for the -arch option: requires a value!\n");
			ft_putstr_fd(buf.str, 2);
			buffer_deinit(&buf);
		}
		return (false);
	}
	env->default_arch = false;
	if (ft_strcmp("all", (*av)[*i + 1]) == 0)
		env->all_archs = true;
	else if ((err = arch_push_arg(&(env->archs), (*av)[*i + 1])) &&
			arch_fatal_err(env->name, env->archs, (*av)[*i + 1], err))
		return (arch_deinit(env->archs));
	*i += 2;
	return (true);
}

t_bool			otool_init_env(int *ac, char const **av[], t_env *env)
{
	int		i;

	env->name = (*av)[0];
	env->archs = NULL;
	env->default_arch = true;
	i = 1;
	while (i < *ac)
	{
		if (ft_strcmp("--", (*av)[i]) == 0)
		{
			i++;
			break ;
		}
		else if (!process_arch_arg(env, ac, av, &i))
			return (false);
		else if (is_opt((*av)[i]))
		{
			usage(env->name, (*av)[i][1]);
			arch_deinit(env->archs);
			return (false);
		}
		else
			break ;
	}
	return (otool_init_env_end(env, ac, av, i));
}
