/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:36:47 by dantonik          #+#    #+#             */
/*   Updated: 2023/04/17 20:33:12 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	anti_aliasing(void)
// {
// 	t_ray	ray;
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < HEIGHT - 1)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			ray = get_ray(x / (double)(WIDTH -1), y / (double)(HEIGHT - 1));
// 			pre_hit(ray, &(data()->px[y][x]), 1000);
// 			pre_hit_obj(ray, &(data()->px[y][x]), 1000);
// 			++x;
// 		}
// 		++y;
// 	}
// }

void	pre_hit_loop(void)
{
	t_ray	ray;
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(x / (double)(WIDTH -1), y / (double)(HEIGHT - 1));
			pre_hit(ray, &(data()->px[y][x]), 1000);
			pre_hit_obj(ray, &(data()->px[y][x]), 1000);
			++x;
		}
		++y;
	}
}

bool	pre_hit(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	double	t;

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
	return (true);
}

void	pre_hit_obj(t_ray ray, t_pixel *px, double t_max)
{
	int		i;
	double	m;

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
		px->normal = data()->objects[i].normal;
	vec3_normalize(&px->normal);
	set_face_normal(ray, &px->normal);
	px->material = data()->objects[i].material;
	px->color = data()->objects[i].color;
	px->fuzz = data()->objects[i].fuzz;
	px->specular = data()->objects[i].specular;
}
