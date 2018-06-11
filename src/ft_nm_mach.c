/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_mach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:55 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 16:56:38 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft/print.h"
#include "libft/libc.h"
#include "libft/buffer.h"

static void	sort_entries(t_mach *obj, struct nlist_64 const **arr)
{
	struct nlist_64 const *tmp;
	uint32_t	i;
	uint32_t	j;
	int ret;
	
	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			//XXX: null strings
			if ((ret = ft_strcmp(ft_mach_get_string_by_symbol(obj, arr[i]),
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
	for (int i = 0; i < obj->symtab_lc->nsyms; i++)
	{
		const char *str = ft_mach_get_string_by_symbol(obj, arr[i]);
		if (str)
			entry_output(obj, arr[i]);
	}
}

t_bool	nm_mach64_wrap(t_mapping map, t_out out, t_list *arch)
{
	struct nlist_64 const	**arr;
	uint32_t				i;
	t_mach					obj;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O_64))
		return (false);
	if (obj.symtab_lc)
	{
		if (!(arr = malloc(sizeof(*arr) * (obj.symtab_lc->nsyms + 1))))
		{
			PERROR("malloc");
			return false;
		}
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

t_bool	nm_mach_wrap(t_mapping map, t_out out, t_list *arch)
{
	struct nlist_64 const	**arr;
	uint32_t				i;
	t_mach					obj;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O))
		return (false);
	if (obj.symtab_lc)
	{
		if (!(arr = malloc(sizeof(*arr) * (obj.symtab_lc->nsyms + 1))))
		{
			PERROR("malloc");
			return false;
		}
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
