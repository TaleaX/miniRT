/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/18 17:24:30 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_obj sphere, t_ray ray)
{
	double	abc[3];
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = vec3_subtraction(sphere.center, ray.origin);
	abc[0] = vec3_dot(ray.direction, ray.direction);
	abc[1] = 2.0 * vec3_dot(oc, ray.direction);
	abc[2] = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (-1);
	t1 = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t2 = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t2 < t1)
		t1 = t2;
	return (t1);
}

double	get_cylinder_return(t_ray ray, t_obj cylinder, double t1, double t2)
{
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

double	hit_cylinder(t_obj cylinder, t_ray ray)
{
	double	abc[3];
	double	discriminant;
	t_vec3	co;
	double	t1;
	double	t2;

	co = vec3_subtraction(cylinder.center, ray.origin);
	abc[0] = vec3_dot(ray.direction, ray.direction) - vec3_dot(ray.direction, \
		cylinder.axis) * vec3_dot(ray.direction, cylinder.axis);
	abc[1] = 2.0 * ((vec3_dot(ray.direction, co) - \
		vec3_dot(ray.direction, cylinder.axis) * vec3_dot(co, cylinder.axis)));
	abc[2] = vec3_dot(co, co) - vec3_dot(co, cylinder.axis) \
		* vec3_dot(co, cylinder.axis) - cylinder.radius * cylinder.radius;
	discriminant = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (-1);
	t1 = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t2 = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	return (get_cylinder_return(ray, cylinder, t1, t2));
}

double	hit_plane(t_obj plane, t_ray ray)
{
	t_vec3	co;
	double	denominator;
	double	numerator;

	co = vec3_scalar(vec3_subtraction(plane.center, ray.origin), -1);
	numerator = vec3_dot(plane.normal, co);
	denominator = vec3_dot(ray.direction, plane.normal);
	if (denominator == 0.0)
		return (-1);
	return (numerator / denominator);
}
