/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 06:30:24 by tdehne           ###   ########.fr       */
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

void	init_spheres(t_obj* spheres)
{
	// init_vec3(&spheres[0].center, 0, 0, 1);
	// init_vec3(&spheres[1].center, 1, 0, 1);
	// init_vec3(&spheres[2].center, -1, 0, 1);
	// init_vec3(&spheres[3].center, 0, -100.5, 0);

	// init_color(&spheres[0].color, 0.7, 0.3, 0.3);
	// init_color(&spheres[1].color, 0.8, 0.6, 0.2);
	// init_color(&spheres[2].color, 0.8, 0.8, 0.8);
	// init_color(&spheres[3].color, 0.8, 0.8, 0.0);

	// spheres[0].radius = 0.5;
	// spheres[1].radius = 0.5;
	// spheres[2].radius = 0.5;
	// spheres[3].radius = 100;

	// spheres[0].material = MIRROR;
	// spheres[1].material = MIRROR;
	// spheres[2].material = MIRROR;
	// spheres[3].material = MATTE;
	double r = cos(M_PI / 4.0);
	init_vec3(&spheres[0].center, 0.5, 0, 3);
	init_vec3(&spheres[1].center, 0, -1000.5, 1);
	init_vec3(&spheres[2].center, -1,    0.0, 2);
	init_vec3(&spheres[3].center, 0,    0.0, 4);
	// init_vec3(&spheres[3].center, 0,    0.0, 1);

	init_color(&spheres[0].color, 0.7, 0.3, 0.3);
	init_color(&spheres[1].color, 0.5, 0.5, 0.5);
	init_color(&spheres[2].color, 0.8, 0.6, 0.2);
	init_color(&spheres[3].color, 0.8, 0.8, 0.8);

	spheres[0].radius = 0.5;
	spheres[1].radius = 1000;
	spheres[2].radius = 0.5;
	spheres[3].radius = 0.5;

	spheres[0].material = MATTE;
	spheres[1].material = MATTE;
	spheres[2].material = MATTE;
	spheres[3].material = MATTE;

	spheres[0].specular = -1;
	spheres[1].specular = -1;
	spheres[2].specular = -1;
	spheres[3].specular = -1;

	spheres[0].fuzz = 0;
	spheres[1].fuzz = 0.0;
	spheres[2].fuzz = 0.0;
	spheres[3].fuzz = 0.3;

	// int i = 4;
	// for (int a = -11; a < 11; a++)
	// {
	// 	for (int b = -11; b < 11; b++)
	// 	{
	// 		double	rand_matterial = random_double();
	// 		t_vec3	center = {a + 0.9*random_double(), -0.4, b + 0.9 * random_double()};
	// 		// t_vec3	lol = vec3_scalar_subtraction(center, vec3_length((t_vec3){4, -0.4, 0}));
	// 		if (vec3_length(vec3_subtraction((t_vec3){4, -0.4, 0}, center)) > 0.9)
	// 		{
	// 			spheres[i].center = center;
	// 			spheres[i].radius = 0.1;
	// 			if (rand_matterial < 0.8) {
	// 				spheres[i].color = (t_color){random_double(), random_double(), random_double(), 1};
	// 				spheres[i].material = MATTE;
	// 				spheres[i].fuzz = 0;
	// 				spheres[i].specular = -1;
	// 			}
	// 			else {
	// 				spheres[i].color = (t_color){random_min_max(0.5, 1), random_min_max(0.5, 1), random_min_max(0.5, 1), 1};
	// 				spheres[i].material = MIRROR;
	// 				spheres[i].fuzz = random_min_max(0, 0.5);
	// 				spheres[i].specular = -1;
	// 			}
	// 			++i;
	// 		}
	// 	}
	// }
	// data()->obj_len = i;
	// init_vec3(&spheres[4].center, 0.2,    -0.4, 0);
	// init_vec3(&spheres[5].center, 0.5,    -0.4, -0.2);
	// init_color(&spheres[4].color, 0.3, 0.0, 0.7);
	// init_color(&spheres[5].color, 0.7, 0.0, 0.3);
	// spheres[4].radius = 0.1;
	// spheres[5].radius = 0.1;
	// spheres[4].material = MATTE;
	// spheres[5].material = MATTE;
	// spheres[4].specular = -1;
	// spheres[5].specular = -1;
	// spheres[4].fuzz = 0.0;
	// spheres[5].fuzz = 0.0;
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

void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
}

void	init_camera(t_camera *camera, double deg)
{
	double	rad;

	rad = degree_to_radian(deg);
	init_vec3(&camera->origin, 0, 0, 0);
	camera->viewport_height = 2 * tanf(rad / 2.0) * VIEWPORT_DIST;
	camera->viewport_width = ASPECT_RATIO * camera->viewport_height;
	// init_ray(&camera->ray, (t_vec3){0, -0.2, -3}, (t_vec3){0, 0, 1});
	// init_vec3(&camera->lower_left_corner, camera->ray.origin.x -VW / 2, camera->ray.origin.y -VH / 2, camera->ray.origin.z - DIST);
}

void	init_light(t_light *light, t_vec3 origin, t_vec3 direction, t_light_type type)
{
	// init_vec3(&light->origin, 0.0, 1.0, 0.0);
	// init_vec3(&light->direction, 1, 1, 1);
	light->ray.origin = origin;
	light->ray.direction = direction;
	light->type = type;
}

// void	init_room(t_room *room)
// {
// 	init_spheres(room->spheres);
// 	init_plane(&room->planes[0]);
// 	init_camera(&room->camera);
// 	init_light(&room->light, (t_vec3){0.0, 1.0, 0.0},  (t_vec3){1.0, 1.0, 1.0}, POINT);
// }

// void	init_window(t_window *window, mlx_image_t *g_img, double height, double width)
// {
// 	window->g_img = g_img;
// 	window->x = 0;
// 	window->y = 0;
// 	window->WIN_HEIGHT = height;
// 	window->WIN_WIDTH = width;
// }


void	init_hit_rec(t_hit_rec *hit_rec, t_vec3 hitpos, t_vec3 normal, double t)
{
	hit_rec->hitpos = hitpos;
	hit_rec->normal = normal;
	hit_rec->t = t;
}

// void	init_sphere(t_obj *sphere, t_vec3 center, double radius, t_material_type material, t_color color)
// {
// 	sphere->center = center;
// 	sphere->radius = radius;
// 	sphere->color = color;
// 	sphere->material = material;
// 	sphere->obj_type = SPHERE;
// }

void	init_data()
{
	// data()->cam_dist = 1;
	init_spheres(data()->objects);
	init_camera(&data()->camera, 90);
	data()->ray.origin = data()->camera.origin;
	// data()->cam_origin = (t_vec3){0, 0, 0};
	init_ray(&(data()->ray), data()->cam_origin, (t_vec3){0, 0, 1});
	data()->light.intensity = 1;
	data()->light.type = POINT;
	init_ray(&data()->light.ray, (t_vec3){0.0, 1.0, 0.0},  (t_vec3){1.0, 1.0, 1.0});
}
