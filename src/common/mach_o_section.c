/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:44:20 by tvallee           #+#    #+#             */
/*   Updated: 2018/05/29 15:42:43 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mach.h"

static t_bool	register_section(t_mach *dst, struct section const *s)
{
	uint8_t i;

	i = 0;
	while (dst->sections[i].b32 != NULL)
	{
		i++;
		if (i == MAX_SECT)
		{
			ft_puterr(NULL, "unsupported binary with more than 255 sections");
			return (false);
		}
	}
	dst->sections[i].b32 = s;
	return (true);
}

t_bool			ft_mach_register_segment(t_mach *dst,
		struct segment_command const *lc, uint32_t index, uint32_t max_len)
{
	uint32_t	i;

	if ((lc->cmdsize - sizeof(*lc)) % sizeof(struct section))
		return (ft_mach_err_lc_size_neq_cmd(index, lc->cmd));
	if (lc->cmdsize != sizeof(*lc) + sizeof(struct section) * lc->nsects)
	{
		ft_puterr(NULL, "inconsistent nsects value");
		return (false);
	}
	if (lc->cmdsize > max_len)
	{
		ft_puterr(NULL, "Malformed MachO file.");
		return (false);
	}
	i = 0;
	while (i < lc->nsects)
	{
		if (!register_section(dst,
					(struct section const*)(lc + 1) + i))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	register_section_64(t_mach *dst, struct section_64 const *s)
{
	uint8_t i;

	i = 0;
	while (dst->sections[i].b64 != NULL)
	{
		i++;
		if (i == MAX_SECT)
		{
			ft_puterr(NULL, "unsupported binary with more than 255 sections");
			return (false);
		}
	}
	dst->sections[i].b64 = s;
	return (true);
}

t_bool			ft_mach_register_segment_64(t_mach *dst,
		struct segment_command_64 const *lc, uint32_t index, uint32_t max_len)
{
	uint32_t	i;

	if ((lc->cmdsize - sizeof(*lc)) % sizeof(struct section_64))
		return (ft_mach_err_lc_size_neq_cmd(index, lc->cmd));
	if (lc->cmdsize != sizeof(*lc) + sizeof(struct section_64) * lc->nsects)
	{
		ft_puterr(NULL, "inconsistent nsects value");
		return (false);
	}
	if (lc->cmdsize > max_len)
	{
		ft_puterr(NULL, "Malformed MachO file.");
		return (false);
	}
	i = 0;
	while (i < lc->nsects)
	{
		if (!register_section_64(dst,
					(struct section_64 const*)(lc + 1) + i))
			return (false);
		i++;
	}
	return (true);
}
