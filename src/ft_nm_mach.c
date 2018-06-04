/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_mach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:55 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/28 15:50:26 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "libft/print.h"

t_bool	nm_mach_wrap(t_mapping map, t_out out, t_list *arch)
{
	t_bool	success;

	success = true;
	/*
	if ((type = get_file_type(map, map.addr)) == E_FILE_MACH_O)
	{

	}
	else if ((type = get_file_type(map, map.addr)) == E_FILE_MACH_O_64)
	{

	}
	else
	{
		return (false);
	}
	*/
	return (true);
}

void	print_entries(t_mach *obj)
{
	struct nlist_64	const *(arr[obj->symtab_lc->nsyms + 1]);
	struct nlist_64 const *tmp;
	int i;
	int j;
	
	for (i = 0; i < obj->symtab_lc->nsyms; i++)
	{
		if (obj->is_64)
			arr[i] = obj->symtab.b64 + i;
		else
			arr[i] = (struct nlist_64 const *)(obj->symtab.b32 + i);
	}
	arr[i] = NULL;
	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			int ret;
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
	
	for (int i = 0; i < obj->symtab_lc->nsyms; i++)
	{
		const char *str = ft_mach_get_string_by_symbol(obj, arr[i]);
		if (str)
			entry_output(obj, arr[i]);
	}
}

t_bool	nm_mach64_wrap(t_mapping map, t_out out, t_list *arch)
{
	t_bool	success;
	t_mach	obj;

	success = true;
	if (!ft_mach_init(&obj, map, E_FILE_MACH_O_64))
		return (false);

	print_entries(&obj);
	return (true);
}
