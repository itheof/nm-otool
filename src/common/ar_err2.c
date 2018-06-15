/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_err2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:37:44 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/15 16:37:58 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ar.h"

/*
** TODO: 111 (characters in size field in archive header are not all
** decimal numbers: 'a' for archive member header at offset 8)
*/

t_bool	ar_err_non_digits_in_size(void)
{
	return (false);
}
