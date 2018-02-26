/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 10:22:04 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/26 21:06:34 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/fat.h>
#include "libft/buffer.h"
#include "libft/swap.h"
#include "common.h"

static t_bool			fat_check_header(t_mapping map, uint32_t *narch)
{
	struct fat_header const	*fat;
	t_buffer				err;

	buffer_init_with(&err, "truncated or malformed fat file");
	fat = map.addr;
	*narch = swap_long(fat->nfat_arch);
	if (*narch == 0)
		buffer_cat(&err, " (contains zero architecture types)");
	else if (!is_large_enough(map, fat + 1, sizeof(struct fat_arch) * *narch))
		buffer_cat(&err, " (fat_arch structs would extend"
				" past the end of the file)");
	else
	{
		buffer_deinit(&err);
		return (true);
	}
	if (err.str != NULL)
		ft_puterr(NULL, err.str);
	buffer_deinit(&err);
	return (false);
}

static struct fat_arch	*fat_to_host_byte_order(t_mapping map, uint32_t narchs)
{
	struct fat_arch	*dest;
	struct fat_arch	*old;
	struct fat_arch *new;
	uint32_t		i;

	if ((dest = malloc(sizeof(*dest) * narchs)) == NULL)
		return (dest);
	i = 0;
	old = (struct fat_arch *)((char*)map.addr + sizeof(struct fat_header));
	new = dest;
	while (i < narchs)
	{
		new->cputype = swap_long(old->cputype);
		new->cpusubtype = swap_long(old->cpusubtype);
		new->offset = swap_long(old->offset);
		new->size = swap_long(old->size);
		new->align = swap_long(old->align);
		old++;
		new++;
		i++;
	}
	return (dest);
}

static t_bool			fat_check_archs(t_mapping map, struct fat_arch *endian,
		uint32_t narchs)
{
	t_buffer	buf;

	while (narchs--)
	{
		if (endian->offset + endian->size > map.size)
		{
			if (buffer_init(&buf))
			{
				buffer_cat(&buf, "truncated or malformed fat file"
						" (offset plus size of cputype (");
				buffer_cat_num(&buf, endian->cputype);
				buffer_cat(&buf, ") cpusubtype (");
				buffer_cat_num(&buf, endian->cpusubtype);
				buffer_cat(&buf, ") extends past the end of the file)");
				if (buf.str)
					ft_puterr(NULL, buf.str);
				buffer_deinit(&buf);
			}
			return (false);
		}
		endian++;
	}
}

static t_err			fat_push_link(t_list **lst, struct fat_arch *addr,
		struct NXArchInfo const *info)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (((t_fat*)current->content)->info.)
	}
}

static t_list			*fat_list_all(struct fat_arch *addr, uint32_t narchs)
{
	t_list	*lst;

	while (narchs--)
	{
		fat_push_link(&lst, addr, );
		addr++;
	}
	return (lst);
}

static t_list			*fat_list(struct fat_arch *addr, uint32_t narchs)
{
	ft_puterr(NULL, "Not implemented yet");
	return (NULL);
}

static t_list			*fat_list_default(struct fat_arch *addr,
		uint32_t narchs)
{
	if (narchs == 1)
	{
		
	}
}

/*
** performs most checks including fat_arch offsets and sizes.
** returns a list of t_fat *
*/
t_list					*fat_init(t_mapping map, t_bool all_archs,
		t_list *arch_infos)
{
	t_list			*lst;
	struct fat_arch	*endian;
	uint32_t		narchs;

	if (is_large_enough(map, map.addr, sizeof(struct fat_header)))
	{
		lst = NULL;
		if (fat_check_header(map, &narchs) &&
				(endian = fat_to_host_byte_order(map, narchs)) != NULL)
		{
			if (fat_check_archs(map, endian, narchs))
			{
				if (all_archs)
					lst = fat_list_all(endian, narchs);
				else if (arch_infos != NULL)
					lst = fat_list(endian, narchs, arch_infos);
				else
					lst = fat_list_default(endian, narchs);
			}
			free(endian);
		}
		return (lst);
	}
	else
		ft_puterr(NULL, ERR_INVALID);
	return (NULL);
}
