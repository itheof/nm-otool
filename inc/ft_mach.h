/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mach.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:39:20 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/29 15:31:50 by tvallee          ###   ########.fr       */
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

# define BIGGEST_CMD_NUM LC_VERSION_MIN_WATCHOS

/*
** Hardcoded ^
*/

# define OBJ_ERROR(x) LLVM_ERROR(x)

t_bool	ft_mach_err_sizeofcmds_lt_file(void);
t_bool	ft_mach_err_lc_past_all_cmds(uint32_t index);
t_bool	ft_mach_err_lc_lt_8(uint32_t index);
t_bool	ft_mach_err_lc_size_not_aligned(uint32_t index);
t_bool	ft_mach_err_lc_size_lt_cmd(uint32_t index, uint32_t cmd);
t_bool	ft_mach_err_lc_size_neq_cmd(uint32_t index, uint32_t cmd);
t_bool	ft_mach_err_symtab_gt_file(void);
t_bool	ft_mach_err_symtab_not_aligned(void);
t_bool	ft_mach_err_strtab_gt_file(void);

t_bool	ft_mach_register_lc(t_mach *dst);

t_bool	ft_mach_load_symtab(t_mach *dst, t_mapping map);
t_bool	ft_mach_register_symtab(t_mach *dst, struct symtab_command const *lc,
		uint32_t index);

t_bool	ft_mach_register_segment(t_mach *dst,
		struct segment_command const *lc, uint32_t index, uint32_t max_len);
t_bool	ft_mach_register_segment_64(t_mach *dst,
		struct segment_command_64 const *lc, uint32_t index, uint32_t max_len);
#endif
