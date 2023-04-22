/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:13:50 by dns               #+#    #+#             */
/*   Updated: 2023/04/22 15:47:05 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_point_light(t_light light)
{
	print_vec3("L:\t\t", light.ray.origin, "");
	printf("\t%f\t\t", light.intensity);
	printf("\t");
	print_color(light.color);
	printf("\n");
}

void	print_sphere(t_obj sphere)
{
	print_vec3("Obj SPHERE:\t", sphere.center, "");
	printf("\t%f\t\t\t", sphere.radius);
	print_color(sphere.color);
	print_mfs(sphere);
}

void	print_plane(t_obj plane)
{
	print_vec3("Obj PLANE:\t", plane.center, "\t");
	print_vec3("", plane.normal, "\t");
	print_color(plane.color);
	print_mfs(plane);
}

void	print_cylinder(t_obj cylinder)
{
	print_vec3("Obj CYL:\t", cylinder.center, "\t");
	print_vec3("", cylinder.normal, "\t");
	print_color(cylinder.color);
	printf("\t%f", cylinder.radius);
	printf("\t%f", cylinder.height);
	print_mfs(cylinder);
}

void	print_scene(int i, int j)
{
	print_camera(data()->camera);
	while ((size_t)i < data()->n_lights)
	{
		if (data()->lights[i].type == AMBIENT)
			print_ambient(data()->lights[i]);
		else if (data()->lights[i].type == POINT)
			print_point_light(data()->lights[i]);
		i++;
	}
	while ((size_t)j < data()->n_objs)
	{
		if (data()->objects[j].obj_type == SPHERE)
			print_sphere(data()->objects[j]);
		else if (data()->objects[j].obj_type == PLANE)
			print_plane(data()->objects[j]);
		else if (data()->objects[j].obj_type == CYLINDER)
			print_cylinder(data()->objects[j]);
		j++;
	}
}
