/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:08 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/06 21:14:32 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

void	vec3_normalize(t_vec3 *v)
{
	double	length;

	length = vec3_length(*v);
	if (length != 0)
	{
		v->x /= length;
		v->y /= length;
		v->z /= length;
	}
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	get_hitpos(t_vec3 ray_origin, t_vec3 ray_direction, double t)
{
	t_vec3	hitpos;

	init_vec3(&hitpos, ray_origin.x + ray_direction.x * t, \
		ray_origin.y + ray_direction.y * t, ray_origin.z + ray_direction.z * t);
	return (hitpos);
}
