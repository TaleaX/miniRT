/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:00 by dns               #+#    #+#             */
/*   Updated: 2023/04/11 13:11:07 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_material(char **line, t_obj *object)
{
	*line += skip_space(*line);
	if (check_floats(*line) < 0)
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

int	get_sphere(char **line)
{
	(*line) += 2;
	parse_skip_three(line, &data()->objects[data()->n_objs].center);
	parse_skip_one(line, &data()->objects[data()->n_objs].radius);
	parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = SPHERE;
	data()->n_objs++;
	return (0);
}

int	get_plane(char **line)
{
	(*line) += 2;
	parse_skip_three(line, &data()->objects[data()->n_objs].center);
	parse_skip_three(line, &data()->objects[data()->n_objs].normal);
	parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = PLANE;
	data()->n_objs++;
	return (0);
}

int	get_cylinder(char **line)
{
	(*line) += 2;
	parse_skip_three(line, &data()->objects[data()->n_objs].center);
	parse_skip_three(line, &data()->objects[data()->n_objs].axis);
	parse_skip_one(line, &data()->objects[data()->n_objs].radius);
	parse_skip_one(line, &data()->objects[data()->n_objs].height);
	parse_skip_color(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	data()->objects[data()->n_objs].obj_type = CYLINDER;
	vec3_normalize(&data()->objects[data()->n_objs].axis);
	data()->n_objs++;
	return (0);
}
