/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:26:13 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 16:42:13 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ar.h"

static unsigned long long	ar_get_numeric_value(char const *str, size_t n)
{
	unsigned long long	ret;
	size_t				i;

	ret = 0;
	i = 0;
	while (ft_isdigit(str[i]) && i < n)
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	return (ret);
}

size_t						ar_name_length(char const *name)
{
	char const *delim;

	delim = ft_memchr(name, ' ', AR_NAME_SIZE);
	if (delim != NULL)
		return (delim - name);
	else
		return (AR_NAME_SIZE);
}

/*
** TODO: Gestion d erreur si (!ft_isdigit)
*/

unsigned long long			ar_header_size(struct ar_hdr const *header)
{
	return (ar_get_numeric_value(header->ar_size, AR_SIZE_SIZE));
}

/*
** TODO: overflow unsigned long long -> size_t ?
*/

size_t						ar_ext_name_length(char const *ar_name)
{
	return (ar_get_numeric_value(ar_name + SAR_EFMT1,
				AR_NAME_SIZE - SAR_EFMT1));
}
