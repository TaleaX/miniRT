/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/18 19:31:56 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	power(double num)
{
	return (num * num);
}

t_color	color_background(t_ray ray)
{
	double	t;
	t_color	color_start;

	t = 0.5*(ray.direction.y + 1.0);
	color_start = (t_color){1, 1, 1, 1};
	color_start = color_scalar(color_start, 1.0 - t , 1);
	return (color_add(color_start, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
}

bool	scatter(t_ray ray, t_ray *scattered, t_color *attenuation, t_pixel *px)
{
	t_vec3	target;
	t_vec3	reflected_dir;
	t_vec3	scattered_dir;
	bool	ref = false;

	if (px->material == MATTE)
	{
		target = vec3_add(px->hitpoint, random_in_hemisphere(px->normal));
		scattered_dir = vec3_subtraction(px->hitpoint, target);
		if (near_zero(scattered_dir))
			scattered_dir = px->normal;
		*scattered = new_ray(px->hitpoint, scattered_dir);
		*attenuation = px->color;
		ref = false;
	}
	if (px->material == MIRROR)
	{
		reflected_dir = reflected_direction(ray.direction, px->normal);
		// t_ray reflected_ray = new_ray(px->hitpoint, vec3_add(reflected_dir, vec3_scalar(random_in_usphere(), px->fuzz)));
		*scattered = new_ray(px->hitpoint, vec3_add(reflected_dir, vec3_scalar(random_in_usphere(), px->fuzz)));
		*attenuation = px->color;
		ref = (vec3_dot(scattered->direction, px->normal) > 0) ? true : false;
	}
	return (ref);
}

// Rekursiv
t_color	color_room(t_ray ray, t_vec2 coord, int depth)
{
	t_color	attenuation;
	t_ray	scattered;
	t_pixel	*px;
	t_color	color;
	t_color	reflected_color;
	t_vec3	v;

	px = &(data()->px[coord.y][coord.x]);
	if (px->obj_id == -1)
		return (color_background(ray));
	hit_obj(ray, px, 1000);
	v = vec3_scalar(ray.direction, -1);
	color = get_color(calc_light(data()->lights, v, *px), px->color);
	if (depth <= 0.0)
		return (color);
	if (px->material == MATTE)
		return (color);
	else if (scatter(ray, &scattered, &attenuation, px))
	{	
		reflected_color = color_mult(attenuation, color_room(scattered, coord, depth - 1));
		return (color_add(color_scalar(color, 0.0, 1), color_scalar(reflected_color, 1, 1)));
	}
	return (color);
}
