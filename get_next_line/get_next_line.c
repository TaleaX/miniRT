/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:40:52 by dantonik          #+#    #+#             */
/*   Updated: 2022/07/27 16:26:11 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*line;
	int			sz;

	if (fd < 0)
		return (NULL);
	buff = ft_calloc(2, 1);
	sz = read(fd, buff, 1);
	if (!sz)
	{
		free(buff);
		return (NULL);
	}
	line = ft_strdup(buff);
	while (sz > 0 && buff[0] != '\n')
	{
		sz = read(fd, buff, 1);
		buff[1] = 0;
		if (sz && buff[0] != '\n')
			line = ft_strjoin(&line, buff);
	}
	free(buff);
	return (line);
}
