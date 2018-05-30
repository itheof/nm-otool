/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o_lc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 12:05:09 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/29 15:40:29 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

static t_bool	ft_mach_check_lc_size(struct load_command const *lc,
		uint32_t max_len,
		uint32_t lc_target_len,
		uint32_t index)
{
	if (max_len < lc_target_len)
	{
		OBJ_ERROR("Malformed MachO file.")
		return (false);
	}
	else if (lc->cmdsize < lc_target_len)
		return (ft_mach_err_lc_size_lt_cmd(index, lc->cmd));
	else
		return (true);
}

static void		ft_mach_lc_dump(struct load_command const *lc, uint32_t max_len)
{
	size_t	len;

	if (lc->cmdsize <= max_len)
		len = lc->cmdsize;
	else
		return ; // this is a corrupt object
	ft_hexdump((const char *)lc, len);
}

static t_bool	ft_mach_switch_lc(t_mach *dst, struct load_command const *lc,
		uint32_t max_len, uint32_t index)
{
	if (lc->cmd == LC_SYMTAB)
		return (ft_mach_check_lc_size(lc, max_len,
					sizeof(struct symtab_command), index) &&
			ft_mach_register_symtab(dst, (struct symtab_command const *)lc, index));
	else if (lc->cmd == LC_SEGMENT && !dst->is_64)
		return (ft_mach_check_lc_size(lc, max_len,
					sizeof(struct segment_command), index) &&
			ft_mach_register_segment(dst, (struct segment_command const *)lc, index, max_len));
	else if (lc->cmd == LC_SEGMENT_64 && dst->is_64)
	{
		return (ft_mach_check_lc_size(lc, max_len,
					sizeof(struct segment_command_64), index) &&
			ft_mach_register_segment_64(dst, (struct segment_command_64 const *)lc, index, max_len));
	}
	return (true);
}

static void		ft_mach_set_lc_start(t_mach *dst)
{
	void const *ptr;

	if (dst->is_64)
		ptr = (struct mach_header_64 const *)dst->header + 1;
	else
		ptr = (struct mach_header const *)dst->header + 1;
	dst->lc_start = (struct load_command const *)ptr;
}

t_bool	ft_mach_register_lc(t_mach *dst)
{
	uint32_t					remaining;
	uint32_t					n;
	struct load_command const	*current;

	ft_mach_set_lc_start(dst);
	dst->symtab_lc = NULL;
	remaining = dst->header->sizeofcmds;
	current = dst->lc_start;
	n = 0;
	while (n < dst->header->ncmds)
	{
		if (remaining < sizeof(*current))
			return (ft_mach_err_lc_past_all_cmds(n));
		else if (current->cmdsize & (0x08 - 1))
			return (ft_mach_err_lc_size_not_aligned(n));
		else if (current->cmdsize < sizeof(*current))
			return (ft_mach_err_lc_lt_8(n));
		/* Checked at the command parsing level
		else if (current->cmdsize > remaining)
			return (ft_mach_err_lc_lt_sizeofcmds(n));*/
		else
		{
			if (!ft_mach_switch_lc(dst, current, remaining, n))
				return (false);

			/* get the next load_command */
			if (current->cmdsize > remaining)
				remaining = 0;
			else
				remaining -= current->cmdsize;
			current = (struct load_command const *)((char const *)current + 
					current->cmdsize);
		}
		n++;
	}
	return (true);
}
