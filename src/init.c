/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/09 15:17:38 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void	init_vec3(t_vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
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
	init_vec3(&spheres[0].center, 0, 0, 0);
	init_vec3(&spheres[1].center, 0, 0, 0);
	init_vec3(&spheres[2].center, 0, 0, 0);
	init_vec3(&spheres[3].center, 0, 0, 0);

	init_color(&spheres[0].color, 1, 0, 0);
	init_color(&spheres[1].color, 0, 1, 0);
	init_color(&spheres[2].color, 0, 0, 1);
	init_color(&spheres[3].color, 0.5, 0.2, 0.5);

	spheres[0].radius = 0.8;
	spheres[1].radius = 0.8;
	spheres[2].radius = 0.8;
	spheres[3].radius = 0.8;
}

void	init_plane(t_plane* plane)
{
	init_vec3(&plane->c, 1, 0, 1);
	init_vec3(&plane->normal, 0, 1, 0);
	init_color(&plane->color, 1, 0, 0);
}


void	init_camera(t_camera *camera)
{
	init_vec3(&camera->ray_origin, 0.0, 5.0, -3.0);
	init_vec3(&camera->ray_direction, 0, 0, 1);
}

void	init_room(t_room *room)
{
	init_spheres(room->spheres);
	init_plane(&room->planes[0]);
	init_camera(&room->camera);
}