/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_mach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:55 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 16:56:38 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"
#include "libft/print.h"
#include "libft/libc.h"
#include "libft/buffer.h"

static int	safe_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strcmp(s1, s2));
}

static void	sort_entries(t_mach *obj, struct nlist_64 const **arr)
{
	struct nlist_64 const	*tmp;
	uint32_t				i;
	uint32_t				j;
	int						ret;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if ((ret = safe_strcmp(ft_mach_get_string_by_symbol(obj, arr[i]),
						ft_mach_get_string_by_symbol(obj, arr[j]))) > 0 ||
					(ret == 0 && arr[i]->n_value > arr[j]->n_value))
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_entries(t_mach *obj, struct nlist_64 const **arr)
{
	uint32_t	i;
	const char	*str;

	i = 0;
	while (i < obj->symtab_lc->nsyms)
	{
		str = ft_mach_get_string_by_symbol(obj, arr[i]);
		if (str)
			;//entry_output(obj, arr[i]);
		i++;
	}
}

/*
** arch is passed in case we want to check for cputype consistency one day
*/

t_bool		otool_mach64_wrap(t_mapping map, t_out out, t_list *arch)
{
	struct nlist_64 const	**arr;
	uint32_t				i;
	t_mach					obj;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O_64) || !ft_match_arch(&obj,
				arch->content))
		return (false);
	if (obj.symtab_lc)
	{
		if (!(arr = malloc(sizeof(*arr) * (obj.symtab_lc->nsyms + 1))))
			return (ft_perror_return_false("malloc"));
		i = 0;
		while (i < obj.symtab_lc->nsyms)
		{
			arr[i] = obj.symtab.b64 + i;
			i++;
		}
		arr[i] = NULL;
		sort_entries(&obj, arr);
		ft_putout(out);
		print_entries(&obj, arr);
		free(arr);
	}
	return (true);
}

t_bool		otool_mach_wrap(t_mapping map, t_out out, t_list *arch)
{
	struct nlist_64 const	**arr;
	uint32_t				i;
	t_mach					obj;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O) || !ft_match_arch(&obj,
				arch->content))
		return (false);
	if (obj.symtab_lc)
	{
		if (!(arr = malloc(sizeof(*arr) * (obj.symtab_lc->nsyms + 1))))
			return (ft_perror_return_false("malloc"));
		i = 0;
		while (i < obj.symtab_lc->nsyms)
		{
			arr[i] = (struct nlist_64 const *)(obj.symtab.b32 + i);
			i++;
		}
		arr[i] = NULL;
		sort_entries(&obj, arr);
		ft_putout(out);
		print_entries(&obj, arr);
		free(arr);
	}
	return (true);
}
