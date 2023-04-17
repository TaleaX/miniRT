/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/17 19:36:16 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_obj sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = vec3_subtraction(sphere.center, ray.origin);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
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

bool	hit_finite(t_ray ray, t_obj cylinder, double t)
{
	t_vec3	hit_point;
	// t_vec3	hit_dir;
	// t_vec3	h;
	double	q_c_len;


	hit_point = get_hitpos(ray.origin, ray.direction, t);
	// hit_dir = vec3_subtraction(cylinder.center, hit_point);
	// h = vec3_scalar(cylinder.axis, cylinder.height);
	q_c_len = vec3_dot(vec3_subtraction(cylinder.center, hit_point) ,cylinder.axis);
	if (q_c_len >= -1 && q_c_len <= cylinder.height+1)
		return (true);
	return (false);
	// return (q_c_len);
}

double	hit_cylinder(t_obj cylinder, t_ray ray)//ray_origin, t_vec3 ray_direction)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	co;
	double	t1;
	double	t2;
	t_vec3	first_hitpoint;
	t_vec3	sec_hitpoint;

	co = vec3_subtraction(cylinder.center, ray.origin);
	a = vec3_dot(ray.direction, ray.direction) - vec3_dot(ray.direction, cylinder.axis) * vec3_dot(ray.direction, cylinder.axis);
	b = 2.0 * ((vec3_dot(ray.direction, co) - vec3_dot(ray.direction, cylinder.axis) * vec3_dot(co, cylinder.axis)));
	c = vec3_dot(co, co) - vec3_dot(co, cylinder.axis) * vec3_dot(co, cylinder.axis) - cylinder.radius * cylinder.radius;
	
	discriminant = b * b - 4.0 * a * c;
	
	if (discriminant < 0.0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	if (hit_finite(ray, cylinder, t1))
	{
		if (hit_finite(ray, cylinder, t2))
		{
			if (t2 < t1)
				return (t2);
		}
		return (t1);
	}
	else if (hit_finite(ray, cylinder, t2))
	{
		return (t2);
	}
	return (-1);
}

double	hit_plane(t_obj plane, t_ray ray)// t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_vec3	co;
	double	denominator;
	double	numerator;
	// double	d_y = ray_direction.y;
	// double	o_y = ray_origin.y;

	co = vec3_scalar(vec3_subtraction(plane.center, ray.origin), -1);

	numerator = vec3_dot(plane.normal, co);
	denominator = vec3_dot(ray.direction, plane.normal);

	if (denominator == 0.0)
		return (-1);
	return (numerator / denominator);
}

t_vec3	get_hitpos2(t_vec3 ray_origin, t_vec3 ray_direction, double t)
{
	return ((t_vec3){ray_origin.x + ray_direction.x * t, ray_origin.y + ray_direction.y * t, 0});
}

bool	hit_obj(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	double	t;
	double m;

	i = 0;
	t = 0;
	px->t = __DBL_MAX__;
	px->obj_id = -1;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == SPHERE)
			t = hit_sphere(data()->objects[i], ray);
		else if (data()->objects[i].obj_type == PLANE)
			t = hit_plane(data()->objects[i], ray);
		else
			t = hit_cylinder(data()->objects[i], ray);
		if (t > 0.001 && t < px->t && t <= t_max)
		{
			px->obj_id = i;
			px->t = t;
		}
		++i;
	}
	if (px->obj_id == -1)
		return (false);
	i = px->obj_id;
	px->hitpoint = get_hitpos(ray.origin, ray.direction, px->t);
	if (data()->objects[i].obj_type == SPHERE)
		px->normal = vec3_subtraction(data()->objects[i].center, px->hitpoint);
	else if (data()->objects[i].obj_type == CYLINDER)
	{
		m = vec3_dot(vec3_subtraction(data()->objects[i].center, px->hitpoint),data()->objects[i].axis);
		px->normal = vec3_subtraction(vec3_scalar(data()->objects[i].axis, m), vec3_subtraction(data()->objects[i].center, px->hitpoint));
	}
	else if (data()->objects[i].obj_type == PLANE)
	{
		px->normal = data()->objects[i].normal;
	}
	vec3_normalize(&px->normal);
	set_face_normal(ray, &px->normal);
	px->material = data()->objects[i].material;
	px->color = data()->objects[i].color;
	px->fuzz = data()->objects[i].fuzz;
	px->specular = data()->objects[i].specular;
	return (true);
}
