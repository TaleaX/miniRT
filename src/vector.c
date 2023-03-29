/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:08 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 03:55:58 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

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
	if (length != 0) {
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

t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z});
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3	vec3_scalar(t_vec3 vec, double scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_vec3	vec3_get_normal(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x - vec2.z, vec1.y * vec2.x - vec1.x - vec2.y});
}

t_vec3	vec3_scalar_subtraction(t_vec3 vec, double scalar)
{
	return ((t_vec3){vec.x - scalar, vec.y - scalar, vec.z - scalar});
}




t_color	color_add(t_color color1, t_color color2)
{
	return ((t_color){color1.r + color2.r, color1.g + color2.g, color1.b + color2.b, color2.a});
}

t_color color_scalar(t_color color, double scalar, double alpha)
{
	return ((t_color){color.r * scalar, color.g * scalar, color.b * scalar, color.a * alpha});
}

t_color color_add_vec(t_color color, t_vec3 vec)
{
	return ((t_color){color.r + vec.x, color.g + vec.y, color.b + vec.z, 1});
}

t_color	color_mult(t_color color1, t_color color2)
{
	return ((t_color){color1.r * color2.r, color1.g * color2.g, color1.b * color2.b, color1.a * color2.a});
}