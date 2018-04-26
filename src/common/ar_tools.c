/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:26:13 by tvallee           #+#    #+#             */
/*   Updated: 2018/04/26 10:35:00 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ar.h"

size_t	ar_name_length(char const *name)
{
	char const *delim;

	delim = ft_memchr(name, ' ', AR_NAME_SIZE);
	if (delim != NULL)
		return (delim - name);
	else
		return (AR_NAME_SIZE);
}
