/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:54:08 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/13 18:28:28 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

t_bool	no_arch(NXArchInfo *info)
{
	t_buffer	buf;

	if (buffer_init(&buf))
	{
		buffer_cat(&buf, "does not contain architechture: ");
		buffer_cat(&buf, info->name);
		buffer_cat(&buf, ".");
		ft_puterr(NULL, buf.str);
		buffer_deinit(&buf);
	}
	return (false);
}

static t_mapping	make_mapping(t_mapping map, struct fat_arch_64 *target)
{
	t_mapping sub;

	sub.mallocd = false;
	sub.path = map.path;
	sub.size = target->size;
	sub.addr = (const char *)map.addr + target->offset;
	return (sub);
}

static t_bool iter_all_required_archs(t_fat *obj, t_arch_fun f, t_mapping map, t_out out)
{
	return (false);
}

static t_bool iter_all_archs(t_fat *obj, t_arch_fun f, t_mapping map, t_out out)
{
	return (false);
}

t_bool	fat_iter(t_fat *obj, t_arch_fun f, t_mapping map, t_out out)
{
	NXArchInfo const	*tmp;
	struct fat_arch_64	*target;
	t_bool				success;

	if (!obj->all_archs)
	{
		if (obj->arch->content == DEFAULT_ARCH)
		{
			tmp = NXGetArchInfoFromName("x86_64");
			if ((target = NXFindBestFatArch_64(tmp->cputype, tmp->cpusubtype,
							obj->arr, obj->narchs)))
				success = f(make_mapping(map, target), out, obj->arch);
			else
				success = iter_all_archs(obj, f, map, out);

		}
		else
		{
			ft_putendl("hello");
			success = iter_all_required_archs(obj, f, map, out);
		}
	}
	else
		success = iter_all_archs(obj, f, map, out);
	return (success);
}
