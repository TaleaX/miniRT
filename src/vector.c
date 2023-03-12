/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:08 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 16:47:59 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
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

// void	change_coords(void *self, double x, double y, double z)
// {
// 	t_vec3	*this;

// 	this = self;
// 	this->x = x;
// 	this->y = y;
// 	this->z = z;
// }

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

t_color	color_add(t_color color1, t_color color2)
{
	return ((t_color){color1.r + color2.r, color1.g + color2.g, color1.b + color2.b, color2.a});
}