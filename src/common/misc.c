/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvallee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:50:26 by tvallee           #+#    #+#             */
/*   Updated: 2018/01/29 13:51:14 by tvallee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/print.h"
#include "libft/string.h"

void	ft_perror(char const *name)
{
	char buf[64];

	if (!ft_strcmp(name, ""))
	{
		ft_strcat(buf, name);
		ft_strcat(buf, ": ");
	}
	ft_strcat(buf, "strerror not allowed\n");
	ft_putendl_fd(buf, 2);
}
