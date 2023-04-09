/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:51:08 by dns               #+#    #+#             */
/*   Updated: 2023/04/09 17:20:16 by dns              ###   ########.fr       */
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

void	print_scene(void)
{
	printf("C:\t\t%f,%f,%f", data()->camera.origin.x, data()->camera.origin.y, data()->camera.origin.z);
	printf("\t%f,%f,%f", data()->camera.lookat.x, data()->camera.lookat.y, data()->camera.lookat.z);
	printf("\t\t\t\t\t%f\n", data()->camera.hfov);
	for (size_t i = 0; i < data()->n_lights; i++)
	{
		if (data()->lights[i].type == AMBIENT)
			printf("AL:\t\t\t\t\t\t%f\t\t\t%f,%f,%f\n", data()->lights[i].intensity, data()->lights[i].color.r, data()->lights[i].color.g, data()->lights[i].color.b);
		else if (data()->lights[i].type == POINT)
		{
			printf("PL:\t\t%f,%f,%f", data()->lights[i].point.x, data()->lights[i].point.y, data()->lights[i].point.z);
			printf("\t%f\t\t", data()->lights[i].intensity);
			printf("\t%f,%f,%f\n", data()->lights[i].color.r, data()->lights[i].color.g, data()->lights[i].color.b);
		}
	}
	for (size_t i = 0; i < data()->n_objs; i++)
	{
		if (data()->objects[i].obj_type == SPHERE)
		{
			printf("Obj %zu (SPHERE):\t%f,%f,%f", i, data()->objects[i].center.x, data()->objects[i].center.y, data()->objects[i].center.z);
			printf("\t%f\t\t",data()->objects[i].radius);
			printf("\t%f,%f,%f\n", data()->objects[i].color.r, data()->objects[i].color.g, data()->objects[i].color.b);
		}
		else if (data()->objects[i].obj_type == PLANE)
		{
			printf("Obj %zu (PLANE):\t%f,%f,%f", i, data()->objects[i].center.x, data()->objects[i].center.y, data()->objects[i].center.z);
			printf("\t%f,%f,%f", data()->objects[i].normal.x, data()->objects[i].normal.y, data()->objects[i].normal.z);
			printf("\t%f,%f,%f", data()->objects[i].color.r, data()->objects[i].color.g, data()->objects[i].color.b);
			printf("\tMaterial:%u Fuzz:%f Specular: %f\n", data()->objects[i].material, data()->objects[i].fuzz, data()->objects[i].specular);
		}
		else if (data()->objects[i].obj_type == CYLINDER)
		{
			printf("Obj %zu (CYL):\t%f,%f,%f", i, data()->objects[i].center.x, data()->objects[i].center.y, data()->objects[i].center.z);
			printf("\t%f,%f,%f", data()->objects[i].normal.x, data()->objects[i].normal.y, data()->objects[i].normal.z);
			printf("\t%f,%f,%f", data()->objects[i].color.r, data()->objects[i].color.g, data()->objects[i].color.b);
			printf("\t%f",data()->objects[i].radius);
			printf("\t%f\n",data()->objects[i].height);

		}
	}
}

int	get_object(char *line)
{
	if (ft_strncmp(line, "sp", 2) == 0)
		get_sphere(line + 2);
	else if (ft_strncmp(line, "A", 1) == 0)
		get_ambientlight(line + 1);
	else if (ft_strncmp(line, "C", 1) == 0)
		get_camera(line + 1);
	else if (ft_strncmp(line, "L", 1) == 0)
		get_light(line + 1);
	else if (ft_strncmp(line, "pl", 2) == 0)
		get_plane(line + 2);
	else if (ft_strncmp(line, "cy", 2) == 0)
		get_cylinder(line + 2);
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

	if (ac != 2)
		return (init_data(), 0);
	if (!(cmp_filename(av)))
		error_handling(0);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		error_handling(1);
	data()->n_objs = 0;
	get_scene(fd);
	// print_scene();
	close (fd);
	return (0);
}