/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/30 15:43:03 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_obj sphere, t_vec3 ray_origin, t_vec3 ray_direction)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = vec3_subtraction(sphere.center, ray_origin);
	a = vec3_dot(ray_direction, ray_direction);
	b = 2.0 * vec3_dot(oc, ray_direction);
	c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	
	discriminant = b * b - 4.0 * a * c;
	
	if (discriminant < 0.0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t2 < t1)
		t1 = t2;
	return (t1);
}


double	hit_plane(t_plane plane, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_vec3	oc;
	double	denominator;
	double	numerator;
	// double	d_y = ray_direction.y;
	// double	o_y = ray_origin.y;

	oc = vec3_subtraction(ray_origin, plane.c);
	numerator = vec3_dot(plane.normal, oc);
	denominator = vec3_dot(ray_direction, plane.normal);
	if (denominator == 0.0)
		return (-1);
	return (numerator / denominator);
}


bool	hit_obj(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	bool	hit;
	double	t;
	double	t_closest;

	i = 0;
	hit = false;
	t = 0;
	t_closest = __DBL_MAX__;
	while (i < data()->obj_len)
	{
		t = hit_sphere(data()->objects[i], ray.origin, ray.direction);
		if (t > 0.001 && t < t_closest && t <= t_max)
		{
			px->hitpoint = get_hitpos(ray.origin, ray.direction, t);
			px->normal = vec3_subtraction(data()->objects[i].center, px->hitpoint);
			vec3_normalize(&px->normal);
			set_face_normal(ray, &px->normal);
			px->t = t;
			px->material = data()->objects[i].material;
			px->color = data()->objects[i].color;
			px->fuzz = data()->objects[i].fuzz;
			px->specular = data()->objects[i].specular;
			// data()->objects[px->obj_id] = room.spheres[i].center;
			px->obj_id = i;
			// rec->radius = room.spheres[i].radius;
			// s = i;
			hit = true;
			t_closest = t;
		}
		++i;

	}
	return (hit);
}