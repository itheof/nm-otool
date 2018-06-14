/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:54:08 by tvallee           #+#    #+#             */
/*   Updated: 2018/06/14 16:08:19 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mach-o/fat.h>
#include <mach-o/loader.h>
#include <stdlib.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

t_bool	no_arch(NXArchInfo const *info)
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
	t_list	*current;
	t_bool	success;
	struct fat_arch_64	*target;
	NXArchInfo const *info;

	current = obj->arch;
	success = true;
	while (current)
	{
		info = current->content;
		if (!(target = NXFindBestFatArch_64(info->cputype, info->cpusubtype,
						obj->arr, obj->narchs)))
			success = no_arch(info);
		else
		{
			out.arch_name = info->name;
			success &= f(make_mapping(map, target), out, current);
		}
		current = current->next;
	}
	return (success);
}

static t_bool iter_all_archs(t_fat *obj, t_arch_fun f, t_mapping map, t_out out)
{
	t_bool				success;
	uint32_t			i;
	NXArchInfo const	*info;
	t_list				tmp;

	i = 0;
	success = true;
	while (i < obj->narchs)
	{
		if ((info = NXGetArchInfoFromCpuType(obj->arr[i].cputype,
						obj->arr[i].cpusubtype)))
			out.arch_name = info->name;
		else
			out.arch_name = ("unknown architechture"
				" (displayed as little endian)");
		tmp.next = NULL;
		tmp.content = (void*)info;
		success &= f(make_mapping(map, obj->arr + i), out, &tmp);
		if (info)
			NXFreeArchInfo(info);
		i++;
	}
	return (success);
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
			success = iter_all_required_archs(obj, f, map, out);
		}
	}
	else
		success = iter_all_archs(obj, f, map, out);
	return (success);
}
