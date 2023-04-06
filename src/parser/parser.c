/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:08 by dns               #+#    #+#             */
/*   Updated: 2023/04/05 14:24:10 by dns              ###   ########.fr       */
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

static int	default_map(t_obj* spheres)
{
	init_vec3(&spheres[0].center, 0.5, 0, 3);
	init_vec3(&spheres[1].center, 0, -1000.5, 1);
	init_vec3(&spheres[2].center, -2,    0.0, 2);
	init_vec3(&spheres[3].center, 0,    0.0, 4);
	// init_vec3(&spheres[3].center, 0,    0.0, 1);

	init_color(&spheres[0].color, 0.7, 0.3, 0.3);
	init_color(&spheres[1].color, 0.5, 0.5, 0.5);
	init_color(&spheres[2].color, 0.8, 0.6, 0.2);
	init_color(&spheres[3].color, 0.8, 0.8, 0.8);

	spheres[0].radius = 0.5;
	spheres[1].radius = 1000;
	spheres[2].radius = 0.5;
	spheres[3].radius = 0.5;

	spheres[0].material = MATTE;
	spheres[1].material = MATTE;
	spheres[2].material = MATTE;
	spheres[3].material = MATTE;

	spheres[0].specular = -1;
	spheres[1].specular = -1;
	spheres[2].specular = -1;
	spheres[3].specular = -1;

	spheres[0].fuzz = 0;
	spheres[1].fuzz = 0.0;
	spheres[2].fuzz = 0.0;
	spheres[3].fuzz = 0.3;
	return(0);
}

int	is_space(int x)
{
	return (x == ' ' || x == '\t' || x == '\r' || x == '\f');
}

int	skip_space(char *input)
{
	int	offset;

	offset = 0;
	while (is_space(input[offset]))
		offset++;
	return (offset);
}

int	get_sphere(char *line)
{
	int	offset;
	t_float	f;
	float	value[3];

	offset = skip_space(line);
	value[0] = parse_float(line+offset, f);
	value[1] = parse_float(line+offset, f);
	value[2] = parse_float(line+offset, f);
	data()->objects[data()->n_objs].center = (t_vec3){value[0], value[1], value[2]};
	// printf("%s\n", line+offset);
	return(0);
}

int	get_object(char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0)
			get_sphere(line+2);
	else if (ft_strncmp(line, "A", 1) == 0)
		printf("Ambient light to be implemented..\n");
	else if (ft_strncmp(line, "C", 1) == 0)
		printf("Camera to be implemented..\n");
	else if (ft_strncmp(line, "L", 1) == 0)
		printf("Light to be implemented..\n");
	else if (ft_strncmp(line, "pl", 2) == 0)
		printf("Plane to be implemented..\n");
	else if (ft_strncmp(line, "cy", 2) == 0)
		printf("Cylinder to be implemented..\n");
	else
		return (1);
	return (0);
}

static int	get_scene(const int fd)
{
	char	*line;
	int		offset;

	line = get_next_line(fd);
	while (line != NULL)
	{
		offset = skip_space(line);
		get_object(line+offset);
		free(line);
		line = get_next_line(fd);
	}
	if(line)
		free(line);
	return(0);
}

int	parser(int ac, char *av)
{
	int	fd;

	if (ac != 2)
		return(init_data(), 0);
	if (!(cmp_filename(av)))
		error_handling(0);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		error_handling(1);
	data()->n_objs = 0;
	get_scene(fd);
	close (fd);
	return(0);
}