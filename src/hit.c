/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 15:55:30 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_sphere sphere, t_vec3 ray_origin, t_vec3 ray_direction)
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
	// t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	// if (t2 < t1)
	// 	t1 = t2;
	return (t1);
}


double	hit_plane(t_plane plane, t_vec3 ray_origin, t_vec3 ray_direction)
{
	t_vec3	oc;
	double	denominator;
	double	numerator;
	double	d_y = ray_direction.y;
	double	o_y = ray_origin.y;

	oc = vec3_subtraction(ray_origin, plane.c);
	numerator = vec3_dot(plane.normal, oc);
	denominator = vec3_dot(ray_direction, plane.normal);
	if (denominator == 0.0)
		return (-1);
	return (numerator / denominator);
}
