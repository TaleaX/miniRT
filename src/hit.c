/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 15:46:38 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_finite(t_ray ray, t_obj cylinder, double t)
{
	t_vec3	hit_point;
	double	q_c_len;

	hit_point = get_hitpos(ray.origin, ray.direction, t);
	q_c_len = vec3_dot(vec3_subtraction(cylinder.center, hit_point), \
			cylinder.axis);
	if (q_c_len >= 0 && q_c_len <= cylinder.height)
		return (true);
	return (false);
}

static void	set_px_data(t_ray ray, t_pixel *px, double t_closest, int i)
{
	double	m;

	px->hitpoint = get_hitpos(ray.origin, ray.direction, t_closest);
	if (data()->objects[i].obj_type == SPHERE)
		px->normal = vec3_subtraction(data()->objects[i].center, px->hitpoint);
	else if (data()->objects[i].obj_type == CYLINDER)
	{
		m = vec3_dot(vec3_subtraction(data()->objects[i].center, px->hitpoint), \
			data()->objects[i].axis);
		px->normal = vec3_subtraction(vec3_scalar(data()->objects[i].axis, m), \
			vec3_subtraction(data()->objects[i].center, px->hitpoint));
	}
	else if (data()->objects[i].obj_type == PLANE)
		px->normal = data()->objects[i].normal;
	vec3_normalize(&px->normal);
	set_face_normal(ray, &px->normal);
	px->t = t_closest;
	px->material = data()->objects[i].material;
	px->color = data()->objects[i].color;
	px->fuzz = data()->objects[i].fuzz;
	px->specular = data()->objects[i].specular;
}

static double	calc_t(t_ray ray, int i)
{
	double	t;

	if (data()->objects[i].obj_type == SPHERE)
		t = hit_sphere(data()->objects[i], ray);
	else if (data()->objects[i].obj_type == PLANE)
		t = hit_plane(data()->objects[i], ray);
	else
		t = hit_cylinder(data()->objects[i], ray);
	return (t);
}

bool	hit_obj(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	bool	hit;
	double	t;
	double	t_closest;

	i = 0;
	hit = false;
	t_closest = __DBL_MAX__;
	while ((size_t)i < data()->n_objs)
	{
		t = calc_t(ray, i);
		if (t > 0.001 && t < t_closest && t <= t_max)
		{
			px->obj_id = i;
			hit = true;
			t_closest = t;
		}
		++i;
	}
	if (hit)
		set_px_data(ray, px, t_closest, px->obj_id);
	return (hit);
}
