/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 17:22:26 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void	init_vec3(void *self, double x, double y, double z)
{
	t_vec3	*this;

	this = self;
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = length;
	this->normalize = normalize;
	this->change_coords = change_coords;
}

void	init_color(t_color *color, double r, double g, double b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 1; 
}

void	init_spheres(t_sphere spheres[4])
{
	init_vec3(&spheres[0].center, 2, 0, -1);
	init_vec3(&spheres[1].center, -1, 0, 2);
	init_vec3(&spheres[2].center, 0, 0, 1);
	init_vec3(&spheres[3].center, 1, 0, 0);

	init_color(&spheres[0].color, 1, 0, 0);
	init_color(&spheres[1].color, 0, 1, 0);
	init_color(&spheres[2].color, 0, 0, 1);
	init_color(&spheres[3].color, 0.5, 0.2, 0.5);

	spheres[0].radius = 0.5;
	spheres[1].radius = 0.5;
	spheres[2].radius = 0.5;
	spheres[3].radius = 0.5;
}