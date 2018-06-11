/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_fat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:30:25 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 18:35:37 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_bool			nm_fat_wrap(t_mapping map, t_out out, t_list *arch)
{
	return (true);
}

t_bool			nm_fat64_wrap(t_mapping map, t_out out, t_list *arch)
{
	t_fat	obj;

	obj.is_64 = true;
	if (!fat_init(map, ))
}
