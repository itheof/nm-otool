/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool_mach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:16:55 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/11 16:56:38 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"
#include "libft/print.h"
#include "libft/libc.h"
#include "libft/buffer.h"

/*
** arch is passed in case we want to check for cputype consistency one day
*/

void		buffer_cat_as_hex(t_buffer *buf, char c)
{
	const char	arr[] = "0123456789abcdef";

	buffer_ncat(buf, arr + ((c & 0xF0) >> 4), 1);
	buffer_ncat(buf, arr + ((c & 0xF)), 1);
}

void		dump_section_64(t_mapping map, struct section_64 const *sect)
{
	uint64_t	i;
	t_buffer	buf;

	if (!buffer_init(&buf))
		return ;
	i = 0;
	while (i < sect->size)
	{
		if (!(i & 0x0F))
		{
			if (i != 0)
				ft_putendl(buf.str);
			buf.len = 0;
			buf.str[0] = 0;
			buffer_cat_value(&buf, sect->addr + i, 16, '0');
			buffer_cat(&buf, "\t");
		}
		buffer_cat_as_hex(&buf, *((const char *)map.addr + sect->offset + i));
		buffer_cat(&buf, " ");
		i++;
	}
	ft_putendl(buf.str);
	buffer_deinit(&buf);
}

void		dump_section(t_mapping map, struct section const *sect)
{
	uint64_t	i;
	t_buffer	buf;

	if (!buffer_init(&buf))
		return ;
	i = 0;
	while (i < sect->size)
	{
		if (!(i & 0x0F))
		{
			if (i != 0)
				ft_putendl(buf.str);
			buf.len = 0;
			buf.str[0] = 0;
			buffer_cat_value(&buf, sect->addr + i, 8, '0');
			buffer_cat(&buf, "\t");
		}
		buffer_cat_as_hex(&buf, *((const char *)map.addr + sect->offset + i));
		buffer_cat(&buf, " ");
		i++;
	}
	ft_putendl(buf.str);
	buffer_deinit(&buf);
}

t_bool		otool_mach64_wrap(t_mapping map, t_out out, t_list *arch)
{
	uint32_t				i;
	t_mach					obj;
	struct section_64 const	*sect;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O_64) || !ft_match_arch(&obj,
				arch->content))
		return (false);
	ft_putout(out, false, false);
	ft_putendl("Contents of (__TEXT,__text) section");
	i = 0;
	while (obj.sections[i].b64)
	{
		sect = obj.sections[i].b64;
		if (!ft_strncmp(sect->segname, "__TEXT", sizeof(sect->segname))
				&& !ft_strncmp(sect->sectname, "__text",
					sizeof(sect->sectname)))
			dump_section_64(map, obj.sections[i].b64);
		i++;
	}
	return (true);
}

t_bool		otool_mach_wrap(t_mapping map, t_out out, t_list *arch)
{
	uint32_t				i;
	t_mach					obj;
	struct section const	*sect;

	if (!ft_mach_init(&obj, map, E_FILE_MACH_O) || !ft_match_arch(&obj,
				arch->content))
		return (false);
	ft_putout(out, false, false);
	ft_putendl("Contents of (__TEXT,__text) section");
	i = 0;
	while (obj.sections[i].b32)
	{
		sect = obj.sections[i].b32;
		if (!ft_strncmp(sect->segname, "__TEXT", sizeof(sect->segname))
				&& !ft_strncmp(sect->sectname, "__text",
					sizeof(sect->sectname)))
			dump_section(map, obj.sections[i].b32);
		i++;
	}
	return (true);
}
