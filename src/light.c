/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:02:00 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 05:06:31 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_lightRay(t_light light, t_vec3 hit_pos)
{
	if (light.type == SUN)
		return (light.ray.direction);
	return(vec3_subtraction(hit_pos, light.ray.origin));
}

double calc_light(t_vec3 light_ray, t_vec3 normal, double intensity)
{
	double	n_dot_l;
	double	light = 0.0;

	n_dot_l = vec3_dot(light_ray, normal);
	if (n_dot_l > 0)
		light = intensity * n_dot_l / (vec3_length(normal) * vec3_length(light_ray));
	return (light);
}

t_vec3	random_in_usphere(void)
{
	t_vec3	random_point;

	while (true)
	{
		// printf("random point x %f %f %f\n", random_point.x, random_point.y, random_point.z);
		init_vec3(&random_point, random_min_max(-1, 1), random_min_max(-1, 1), random_min_max(-1, 1));
		if (vec3_length(random_point) >= 1)
			continue;
		return (random_point);
	}
}