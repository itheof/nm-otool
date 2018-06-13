/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_parse_opt.c                                  :+:      :+:    :+:   */
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
#include "ft_nm.h"

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

static t_bool	is_opt_delimiter(char const *arg)
{
	return (ft_strcmp("--", arg) == 0);
}

static t_bool	is_opt(char const *arg)
{
	return (ft_strlen(arg) > 1 && arg[0] == '-');
}

static t_list	*make_default_arch(void)
{
	return (ft_lstnewcopy(DEFAULT_ARCH, sizeof(void*)));
}

t_bool	nm_init_env(int *ac, char const **av[], t_env *env)
{
	int		i;
	t_err	err;
	t_bool	default_arch;

	env->name = (*av)[0];
	env->archs = NULL;
	default_arch = true;

	i = 1;
	while (i < *ac)
	{
		if (is_opt_delimiter((*av)[i]))
		{
			i++;
			break;
		}
		else if (ft_strcmp("-arch", (*av)[i]) == 0 && i < *ac + 1)
		{
			default_arch = false;
			if (ft_strcmp("all", (*av)[i + 1]) == 0)
				env->all_archs = true;
			else if ((err = arch_push_arg(
							&(env->archs), (*av)[i + 1])) &&
					arch_fatal_err(env->name, env->archs, (*av)[i + 1], err))
			{
				arch_deinit(env->archs);
				return (false);
			}
			i += 2;
		}
		else if (is_opt((*av)[i]))
		{
			usage(env->name, (*av)[i][1]);
			arch_deinit(env->archs);
			return(false);
		}
		else
			break;
	}

	ft_puterr(env->name, NULL);
	if (default_arch)
	{
		if ((env->archs = make_default_arch()) == NULL)
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
