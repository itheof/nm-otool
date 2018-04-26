/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 10:30:50 by tvallee           #+#    #+#             */
/*   Updated: 2018/04/26 10:41:58 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_AR_H
# define FT_AR_H

#include <ar.h>
#include <mach-o/ranlib.h>
#include "libft/libc.h"
#include "libft/buffer.h"
#include "libft/print.h"
#include "common.h"

# define AR_INVALID "truncated or malformed archive"
# define AR_NAME_SIZE sizeof(((struct ar_hdr*)(0))->ar_name)
# define AR_SIZE_SIZE sizeof(((struct ar_hdr*)(0))->ar_size)
# define SAR_EFMT1 (sizeof(AR_EFMT1) - 1) // for \0
# define SARFMAG (sizeof(ARFMAG) - 1) // for \0

t_bool	ar_err_non_digits_in_size();
t_bool	ar_err_non_digits_in_long_name(off_t offset, char const *ar_name);
t_bool	ar_err_too_small_for_header(off_t offset);
t_bool	ar_err_too_small_for_object(t_ar_obj obj);
t_bool	ar_err_too_small_for_ext_name(unsigned long long name_len);
t_bool	ar_err_bad_terminator_chars(t_mapping ar, struct ar_hdr const *header,
		t_ar_obj const *info);
size_t	ar_name_length(char const *name);

#endif
