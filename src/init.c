/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 16:51:07 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	init_vec3(&spheres[0].center, 0, -1, 3);
	init_vec3(&spheres[1].center, 2, 0, 4);
	init_vec3(&spheres[2].center, -2, 0, 4);
	init_vec3(&spheres[3].center, 0, -5001, 0);

	init_color(&spheres[0].color, 0.8, 0.8, 0.8);
	init_color(&spheres[1].color, 0.9, 0.65, 1);
	init_color(&spheres[2].color, 0.6, 1, 0.9);
	init_color(&spheres[3].color, 0.6, 0.8, 1);

	spheres[0].radius = 1;
	spheres[1].radius = 1;
	spheres[2].radius = 1;
	spheres[3].radius = 5000;
}

// void	init_sphere(t_sphere sphere, t_vec3 center, t_color color, double radius)
// {
// 	sphere.color = color;
// 	sphere.radius = radius;
// 	sphere.center = center;
// }

void	init_plane(t_plane* plane)
{
	init_vec3(&plane->c, 0, 0, 0);
	init_vec3(&plane->normal, 0, 1, 0);
	init_color(&plane->color, 1, 0, 0);
}


void	init_camera(t_camera *camera)
{
	init_vec3(&camera->origin, 0.0, 0.0, -12.0);
	init_vec3(&camera->direction, 0, 0, 1);
}

void	init_light(t_light *light, t_vec3 origin, t_vec3 direction, t_light_type type)
{
	// init_vec3(&light->origin, 0.0, 1.0, 0.0);
	// init_vec3(&light->direction, 1, 1, 1);
	light->origin = origin;
	light->direction = direction;
	light->type = type;
}

void	init_room(t_room *room)
{
	init_spheres(room->spheres);
	init_plane(&room->planes[0]);
	init_camera(&room->camera);
	init_light(&room->light, (t_vec3){0.0, 1.0, 0.0},  (t_vec3){1.0, 1.0, 1.0}, POINT);
}

void	init_window(t_window *window, mlx_image_t *g_img, double height, double width)
{
	window->g_img = g_img;
	window->x = 0;
	window->y = 0;
	window->WIN_HEIGHT = height;
	window->WIN_WIDTH = width;
}

void	init_viewport(t_viewport *viewport, double distance, double v_height, double v_width)
{
	t_vec3	dir;

	init_vec3(&viewport->dir, 0, 0, distance);
	viewport->V_HEIGHT = v_height;
	viewport->V_WIDTH = v_width;
}