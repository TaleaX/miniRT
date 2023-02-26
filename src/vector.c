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

double	length(void	*self)
{
	t_vec3	*this;

	this = self;
	return (sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}

void	normalize(void *self)
{
	t_vec3	*this;
	double	length;

	this = self;
	length = this->length(this);
	if (length != 0) {
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}
}

void	change_coords(void *self, double x, double y, double z)
{
	t_vec3	*this;

	this = self;
	this->x = x;
	this->y = y;
	this->z = z;
}

double	dot_produkt(t_vec3 v1, t_vec3 v2)
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

t_vec3	t_vec3_subtraction(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	v;

	init_vec3(&v, vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z);
	return (v);
}
