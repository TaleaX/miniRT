/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:12:22 by dantonik          #+#    #+#             */
/*   Updated: 2023/04/20 17:49:16 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	reflected_direction(t_vec3 lightRay, t_vec3 normal)
{
	double	scalar;

	scalar = vec3_dot(lightRay, normal) * 2;
	return (vec3_subtraction(vec3_scalar(normal, scalar), lightRay));
}

void	set_face_normal(t_ray ray, t_vec3 *outward_normal)
{
	bool	front_face;

	front_face = vec3_dot(ray.direction, *outward_normal) < 0;
	if (!front_face)
		*outward_normal = vec3_scalar(*outward_normal, -1);
}

bool	near_zero(t_vec3 vec)
{
	double	n;

	n = 1e-8;
	return (fabs(vec.x) < n && fabs(vec.y) < n && fabs(vec.z) < n);
}

double	degree_to_radian(double degree)
{
	return (degree * 2 * M_PI / 360.0);
}

t_ray	get_ray(double h, double v)
{
	t_ray	ray;
	t_vec3	x;
	t_vec3	y;
	t_vec3	viewport_px;

	x = vec3_scalar(data()->camera.viewport_horizontal, h);
	y = vec3_scalar(data()->camera.viewport_vertical, v);
	viewport_px = vec3_add(data()->camera.lower_left_corner, vec3_add(x, y));
	ray.origin = data()->camera.origin;
	ray.direction = vec3_subtraction(ray.origin, viewport_px);
	return (ray);
}
