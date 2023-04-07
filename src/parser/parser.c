/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:08 by dns               #+#    #+#             */
/*   Updated: 2023/04/06 22:11:40 by dns              ###   ########.fr       */
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

t_color	color_parsed(void)
{
	return ((t_color){data()->parse_float[0] / 255, data()->parse_float[1] / 255, data()->parse_float[2] / 255, 1});
}

int	get_sphere(char *line)
{
	line += skip_space(line);
	parse_floats(line);
	data()->objects[data()->n_objs].center = (t_vec3){data()->parse_float[0], data()->parse_float[1], data()->parse_float[2]};
	while ((*line >= '0' && *line <= '9') || *line == '.' || *line == ',')
		line++;
	line += skip_space(line);
	data()->objects[data()->n_objs].radius = (parse_float(line)) / 2;
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	line += skip_space(line);
	parse_floats(line);
	// data()->objects[data()->n_objs].color = (t_color){data()->parse_float[0], data()->parse_float[1], data()->parse_float[2], 1.0f};
	data()->objects[data()->n_objs].color = color_parsed();
	data()->objects[data()->n_objs].obj_type = SPHERE;
	data()->n_objs++;
	return(0);
}

int	get_light(char *line)
{
	line += skip_space(line);
	parse_floats(line);
	data()->lights[data()->n_lights].point = (t_vec3){data()->parse_float[0], data()->parse_float[1], data()->parse_float[2]};
	while ((*line >= '0' && *line <= '9') || *line == '.' || *line == ',')
		line++;
	line += skip_space(line);
	data()->lights[data()->n_lights].intensity = parse_float(line);
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	line += skip_space(line);
	parse_floats(line);
	// data()->objects[data()->n_objs].color = (t_color){data()->parse_float[0], data()->parse_float[1], data()->parse_float[2], 1.0f};
	data()->lights[data()->n_lights].color = color_parsed();
	data()->lights[data()->n_lights].type = POINT;
	data()->n_lights++;
	return(0);
}

int	get_ambientlight(char *line)
{
	line += skip_space(line);
	data()->lights[data()->n_lights].intensity = parse_float(line);
	while ((*line >= '0' && *line <= '9') || *line == '.')
		line++;
	line += skip_space(line);
	parse_floats(line);
	data()->lights[data()->n_lights].color = (t_color){data()->parse_float[0], data()->parse_float[1], data()->parse_float[2], 1};
	data()->lights[data()->n_lights].type = AMBIENT;
	data()->n_lights++;
	return (0);
}

int	get_object(char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		get_sphere(line+2);
	else if (ft_strncmp(line, "A", 1) == 0)
		get_ambientlight(line+1);
	else if (ft_strncmp(line, "C", 1) == 0)
		printf("Camera to be implemented..\n");
	else if (ft_strncmp(line, "L", 1) == 0)
		get_light(line+1);
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

void	print_scene(void)
{
	for (size_t i = 0; i < data()->n_objs; i++)
	{
		printf("Obj %zu: center %f,%f,%f", data()->n_objs, data()->objects[i].center.x, data()->objects[i].center.y, data()->objects[i].center.z);
		printf("\t%f",data()->objects[i].radius*2);
		printf("\t%f,%f,%f\n", data()->objects[i].color.r, data()->objects[i].color.g, data()->objects[i].color.b);
	}
	for (size_t i = 0; i < data()->n_lights; i++)
	{
		if (data()->lights[i].type == AMBIENT)
			printf("Ambient light: %f\t%f,%f,%f\n", data()->lights[i].intensity, data()->lights[i].color.r, data()->lights[i].color.g, data()->lights[i].color.b);
		if (data()->lights[i].type == POINT)
		{
			printf("Point light: %f,%f,%f", data()->lights[i].point.x, data()->lights[i].point.y, data()->lights[i].point.z);
			printf("\t%f", data()->lights[i].intensity);
			printf("\t%f,%f,%f\n", data()->lights[i].color.r, data()->lights[i].color.g, data()->lights[i].color.b);
		}
	}
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
	print_scene();
	close (fd);
	return(0);
}