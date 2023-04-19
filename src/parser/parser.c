/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:08 by dns               #+#    #+#             */
/*   Updated: 2023/04/17 14:40:49 by tdehne           ###   ########.fr       */
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

int	get_object(char *line)
{
	if (*line == '#')
		return (0);
	else if (ft_strncmp(line, "sp", 2) == 0)
		get_sphere(&line);
	else if (ft_strncmp(line, "A", 1) == 0)
		get_ambientlight(&line);
	else if (ft_strncmp(line, "C", 1) == 0)
		get_camera(&line);
	else if (ft_strncmp(line, "L", 1) == 0)
		get_light(&line);
	else if (ft_strncmp(line, "pl", 2) == 0)
		get_plane(&line);
	else if (ft_strncmp(line, "cy", 2) == 0)
		get_cylinder(&line);
	else if (ft_strncmp(line, "S", 1) == 0)
		get_sun(&line);
	else
		return (1);
	return (0);
}

int	get_scene(const int fd)
{
	char	*line;
	int		offset;

	line = get_next_line(fd);
	while (line != NULL)
	{
		offset = skip_space(line);
		get_object(line + offset);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (0);
}

int	parser(int ac, char *av)
{
	int	fd;

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
	get_scene(fd);
	printf("sun light %f %f %f\n", data()->lights[1].ray.direction.x, data()->lights[1].ray.direction.y, data()->lights[1].ray.direction.z);
	print_scene(0, 0);
	close (fd);
	return (0);
}
