/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_get_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:10:00 by dns               #+#    #+#             */
/*   Updated: 2023/04/23 20:51:35 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_material(char **line, t_obj *object)
{
	(*line) += skip_space(*line);
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

int	get_sphere(char **line, int i)
{
	(*line) += 2;
	i += parse_skip_three_err(line, &data()->objects[data()->n_objs].center);
	i += parse_skip_one_err(line, &data()->objects[data()->n_objs].radius);
	i += parse_skip_color_err(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	if (i > 0)
		return (-1);
	data()->objects[data()->n_objs].obj_type = SPHERE;
	data()->n_objs++;
	return (0);
}

int	get_plane(char **line, int i)
{
	(*line) += 2;
	i += parse_skip_three_err(line, &data()->objects[data()->n_objs].center);
	i += parse_skip_three_err(line, &data()->objects[data()->n_objs].normal);
	i += parse_skip_color_err(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	if (i > 0)
		return (-1);
	data()->objects[data()->n_objs].obj_type = PLANE;
	data()->n_objs++;
	return (0);
}

int	get_cylinder(char **line, int i)
{
	(*line) += 2;
	i += parse_skip_three_err(line, &data()->objects[data()->n_objs].center);
	i += parse_skip_three_err(line, &data()->objects[data()->n_objs].axis);
	i += parse_skip_one_err(line, &data()->objects[data()->n_objs].radius);
	i += parse_skip_one_err(line, &data()->objects[data()->n_objs].height);
	i += parse_skip_color_err(line, &data()->objects[data()->n_objs].color);
	get_material(line, &data()->objects[data()->n_objs]);
	if (i > 0)
		return (-1);
	data()->objects[data()->n_objs].obj_type = CYLINDER;
	vec3_normalize(&data()->objects[data()->n_objs].axis);
	data()->n_objs++;
	return (0);
}
