/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:19:27 by dns               #+#    #+#             */
/*   Updated: 2023/04/09 17:12:32 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_sphere(char *line)
{
	line = parse_skip_three(line, &data()->objects[data()->n_objs].center);
	line = parse_skip_one(line, &data()->objects[data()->n_objs].radius);
	line = parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = SPHERE;
	data()->n_objs++;
	return (0);
}

int	get_light(char *line)
{
	line = parse_skip_three(line, &data()->lights[data()->n_lights].point);
	line = parse_skip_one(line, &data()->lights[data()->n_lights].intensity);
	line = parse_skip_color(line, &data()->lights[data()->n_lights].color);
	data()->lights[data()->n_lights].type = POINT;
	data()->n_lights++;
	return (0);
}

int	get_ambientlight(char *line)
{
	line = parse_skip_one(line, &data()->lights[data()->n_lights].intensity);
	line = parse_skip_color(line, &data()->lights[data()->n_lights].color);
	data()->lights[data()->n_lights].type = AMBIENT;
	data()->n_lights++;
	return (0);
}

int	get_material(char *line, t_obj *object)
{
	line += skip_space(line);
	if (check_floats(line) < 0)
	{
		object->material = 0;
		object->fuzz = 0;
		object->specular = -1;
		return (-1);
	}
	parse_floats(line);
	object->material = (t_material_type)data()->parse_float[0];
	object->fuzz = data()->parse_float[1];
	object->specular = data()->parse_float[2];
	return (0);
}

int	get_plane(char *line)
{
	line = parse_skip_three(line, &data()->objects[data()->n_objs].center);
	line = parse_skip_three(line, &data()->objects[data()->n_objs].normal);
	line = parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = PLANE;
	data()->n_objs++;
	return (0);
}

int	get_cylinder(char *line)
{
	line = parse_skip_three(line, &data()->objects[data()->n_objs].center);
	line = parse_skip_three(line, &data()->objects[data()->n_objs].normal);
	line = parse_skip_one(line, &data()->objects[data()->n_objs].radius);
	line = parse_skip_one(line, &data()->objects[data()->n_objs].height);
	line = parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = CYLINDER;
	data()->n_objs++;
	return (0);
}

int	get_camera(char *line)
{
	line = parse_skip_three(line, &data()->camera.origin);
	line = parse_skip_three(line, &data()->camera.lookat);
	line = parse_skip_one(line, &data()->camera.hfov);
	return (0);
}
