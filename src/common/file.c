/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:10:50 by tvallee           #+#    #+#             */
/*   Updated: 2018/02/12 16:25:46 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "common.h"
#include "libft/string.h"

static int		get_fd(const char *path, t_mapping *map, const char *name)
{
	int	fd;

	if (!ft_strcmp(path, "-"))
	{
		map->path = "<stdin>";
		return (0);
	}
	else
	{
		map->path = path;
		if ((fd = open(map->path, O_RDONLY)) < 0)
		{
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			PERROR(map->path);
		}
		return (fd);
	}
}

static t_bool	map_regular_file(struct stat buf, t_mapping *map, int fd,
		const char *name)
{
	char	*tmp;
	char	*tmp_bis;

	map->size = buf.st_size;
	map->addr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map->addr == MAP_FAILED)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
		PERROR("mmap");
		return (false);
	}
	map->_mallocd = false;
	if ((tmp = ft_strjoin(name, ": ")) != NULL)
	{
		if ((tmp_bis = ft_strjoin(tmp, map->path)) != NULL)
		{
			free(tmp);
			if ((tmp = ft_strjoin(tmp_bis, " ")) != NULL)
				ft_puterr(tmp, NULL);
			free(tmp_bis);
		}
		free(tmp);
	}
	return (true);
}

static t_bool	map_special_file(struct stat buf, t_mapping *map, int fd,
		const char *name)
{
	char	*tmp;
	char	*tmp_bis;

	(void)buf;
	(void)map;
	(void)fd;
	(void)name;
	if ((tmp_bis = ft_strjoin(": ", map->path)))
	{
		if ((tmp = ft_strjoin(tmp_bis,
						": non-regular file mapping not implemented: "
						"read not allowed")) != NULL)
		{
			ft_puterr(NULL, tmp);
			free(tmp);
		}
		free(tmp_bis);
	}
	return (false);
}

t_bool			map_file(const char *path, t_mapping *map, const char *name)
{
	struct stat	buf;
	int			fd;

	if ((fd = get_fd(path, map, name)) < 0)
		return (false);
	if (fstat(fd, &buf) < 0)
	{
		PERROR("fstat");
		return (false);
	}
	if (buf.st_mode & S_IFREG)
	{
		return (map_regular_file(buf, map, fd, name));
	}
	else
	{
		return (map_special_file(buf, map, fd, name));
	}
}

void	unmap_file(t_mapping *map)
{
	if (!map->_mallocd)
	{
		munmap(map->addr, map->size);
	}
}
