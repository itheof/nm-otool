/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mach.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:39:20 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/23 17:14:59 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MACH_H
# define FT_MACH_H

# include "libft/libc.h"
# include "libft/buffer.h"
# include "libft/print.h"
# include "common.h"

# define OBJ_INVALID "truncated or malformed object"


# define LLVM_ERROR(x) dprintf(2, "LLVM ERROR: %s\n", x);
# define FT_NM_ERROR(x) ft_puterr(NULL, "Mach-O error: " x);

# define OBJ_ERROR(x) LLVM_ERROR(x)

t_bool	ft_mach_err_sizeofcmds_lt_file(void);
t_bool	ft_mach_err_lc_past_all_cmds(uint32_t index);
t_bool	ft_mach_err_lc_lt_8(uint32_t index);
t_bool	ft_mach_err_lc_size_not_aligned(uint32_t index);

#endif
