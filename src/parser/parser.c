/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:08 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 15:30:41 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	cmp_filename(const char *s1)
{
	int		i;
	int		j;
	char	*s2;

	s2 = ".rt";
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	i -= 3;
	while (s1[i] && (s1[i] == s2[j]))
	{
		i++;
		j++;
	}
	if (j != 3)
	{
		printf("The file has to end with .rt!\n");
		return (false);
	}
	return (true);
}

int	get_object(char *line, int i)
{
	if (*line == '#')
		return (0);
	else if (ft_strncmp(line, "R", 1) == 0)
		i = get_resolution(&line, i);
	else if (ft_strncmp(line, "sp", 2) == 0)
		i = get_sphere(&line, i);
	else if (ft_strncmp(line, "A", 1) == 0)
		i = get_ambientlight(&line, i);
	else if (ft_strncmp(line, "C", 1) == 0)
		i = get_camera(&line, i);
	else if (ft_strncmp(line, "L", 1) == 0)
		i = get_light(&line, i);
	else if (ft_strncmp(line, "pl", 2) == 0)
		i = get_plane(&line, i);
	else if (ft_strncmp(line, "cy", 2) == 0)
		i = get_cylinder(&line, i);
	else if (ft_strncmp(line, "S", 1) == 0)
		i = get_sun(&line, i);
	else
		return (1);
	if (i == -1)
		return (-1);
	return (0);
}

int	get_scene(const int fd)
{
	char	*line;
	int		offset;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		offset = skip_space(line);
		i = get_object(line + offset, 0);
		if (i == -1)
		{
			printf("Error on line: %s\n", line);
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (i);
}

int	parser(int ac, char *av)
{
	int	fd;
	int	i;

	if (ac == 2)
	{
		if (!(cmp_filename(av)))
			error_handling(0);
		fd = open(av, O_RDONLY);
	}
	else
		fd = open("scenes/cool_room.rt", O_RDONLY);
	if (fd < 0)
		error_handling(1);
	data()->n_objs = 0;
	i = get_scene(fd);
	data()->aspect_ratio = (double)data()->width / (double)data()->height;
	init_camera(&data()->camera, (t_vec3){0, 1, 0});
	close (fd);
	if (i == -1 || (data()->camera.orientation.x == 0 \
	&& data()->camera.orientation.y == 0 && data()->camera.orientation.z == 0))
		return (-1);
	return (0);
}
