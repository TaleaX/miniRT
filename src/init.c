/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/06 20:23:40 by dns              ###   ########.fr       */
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
	//double r = cos(M_PI / 4.0);
	init_vec3(&spheres[0].center, 0.5, 1, 2);
	init_vec3(&spheres[1].center, 0, -5001, 1);
	init_vec3(&spheres[2].center, -2,   0, 2);
	init_vec3(&spheres[3].center, 2,    0, 4);
	// init_vec3(&spheres[3].center, 0,    0.0, 1);

	init_color(&spheres[0].color, 0.7, 0.3, 0.3);
	init_color(&spheres[1].color, 0.5, 0.5, 0.5);
	init_color(&spheres[2].color, 0.8, 0.55, 1);
	init_color(&spheres[3].color, 0.8, 0.8, 0.8);

	spheres[0].radius = 1.0;
	spheres[1].radius = 5000;
	spheres[2].radius = 1.0;
	spheres[3].radius = 1.0;

	spheres[0].material = MIRROR;
	spheres[1].material = MIRROR;
	spheres[2].material = MATTE;
	spheres[3].material = MATTE;

	spheres[0].specular = -1;
	spheres[1].specular = 1000;
	spheres[2].specular =  10;
	spheres[3].specular =  500;

	spheres[0].fuzz = 0;
	spheres[1].fuzz = 0.0;
	spheres[2].fuzz = 0.0;
	spheres[3].fuzz = 0.0;

	spheres[0].obj_type = SPHERE;
	spheres[1].obj_type = SPHERE;
	spheres[2].obj_type = SPHERE;
	spheres[3].obj_type = SPHERE;

	int i = 4;
	for (int a = -2; a < 3; a++)
	{
		for (int b = -2; b < 3; b++)
		{
			double	rand_matterial = random_double();
			t_vec3	center = {a + 0.9*random_double(), -0.8, b + 0.9 * random_double()};
			// t_vec3	lol = vec3_scalar_subtraction(center, vec3_length((t_vec3){4, -0.4, 0}));
			if (vec3_length(vec3_subtraction((t_vec3){4, -0.8, 0}, center)) > 0.9)
			{
				spheres[i].center = center;
				spheres[i].radius = 0.2;
				if (rand_matterial < 0.01) {
					spheres[i].color = (t_color){random_double(), random_double(), random_double(), 1};
					spheres[i].material = MATTE;
					spheres[i].fuzz = 0;
					spheres[i].specular = -1;
					spheres[i].obj_type = SPHERE;
				}
				else {
					spheres[i].color = (t_color){random_min_max(0.5, 1), random_min_max(0.5, 1), random_min_max(0.5, 1), 1};
					spheres[i].material = MIRROR;
					spheres[i].fuzz = random_min_max(0, 0.1);
					spheres[i].specular = -1;
					spheres[i].obj_type = SPHERE;

				}
				++i;
			}
		}
	}
	data()->obj_len = i;
}

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

void	init_camera(t_camera *camera, double vfov, t_vec3 origin, t_vec3 vup, t_vec3 lookat, double focus_dist, double aperture)
{
	double	vfov_rad;
	double	viewport_width;
	double	viewport_height;
	// t_vec3	w;
	// t_vec3	v;
	// t_vec3	u;
	t_vec3	negative_offset;

	vfov_rad = degree_to_radian(vfov);
	camera->origin = origin;
	camera->lookat = lookat;

	camera->w = vec3_subtraction(origin, lookat);
	vec3_normalize(&camera->w);
	camera->u = vec3_get_normal(vup, camera->w);
	vec3_normalize(&camera->u);
	camera->v = vec3_get_normal(camera->w, camera->u);

	viewport_height = 2 * tanf(vfov_rad / 2.0) * VIEWPORT_DIST;
	viewport_width = ASPECT_RATIO * viewport_height;

	// init_vec3(&(camera->viewport_vertical), 0, viewport_height, 0);
	// init_vec3(&(camera->viewport_horizontal), viewport_width, 0, 0);

	camera->viewport_vertical = vec3_scalar(camera->v, viewport_height); //* focus_dist);//viewport_height * v;//vec3_mult(camera->viewport_vertical, v);
	camera->viewport_horizontal = vec3_scalar(camera->u, viewport_width);// * focus_dist);// * u;//vec3_mult(camera->viewport_horizontal, u);

	camera->lower_left_corner = vec3_subtraction(vec3_scalar(camera->viewport_horizontal,  0.5), camera->origin);
	camera->lower_left_corner = vec3_subtraction(vec3_scalar(camera->viewport_vertical,  0.5), camera->lower_left_corner);
	// negative_offset = vec3_subtraction(vec3_scalar(camera->viewport_vertical,  0.5), vec3_scalar(camera->viewport_horizontal,  0.5));
	// negative_offset = vec3_add(negative_offset, w);
	camera->lower_left_corner = vec3_add(camera->w, camera->lower_left_corner);
	//vec3_scalar(camera->w, focus_dist)
	// camera->lower_left_corner.x -= w.x;
	// camera->lower_left_corner.y -= w.y;
	// camera->lower_left_corner.z -= w.z;
	camera->lens_radius = aperture / 2.0;
}

void	init_lights(t_light *lights)
{
	lights[0].intensity = 0.2;
	lights[0].type = AMBIENT;

	lights[1].intensity = 0.6;
	lights[1].type = POINT;
	init_ray(&lights[1].ray, (t_vec3){4.0, 3.0, -3.0},  (t_vec3){0, 0.0, 0.0});

	// init_ray(&lights[0].ray, (t_vec3){2.0, 1.0, 0.0},  (t_vec3){0, 0.0, 0.0});

	lights[2].intensity = 0.2;
	lights[2].type = SUN;
	init_ray(&lights[2].ray, (t_vec3){0.0, 0.0, 0.0},  (t_vec3){1, 4.0, 4.0});

	data()->lights_len = 3;
}
void	init_planes(t_obj *planes)
{
	int i;

	i = data()->obj_len - 1;
	planes[i].center = (t_vec3){1, 1, 8};
	planes[i].normal = (t_vec3){0, 0, -1};
	planes[i].obj_type = PLANE;
	planes[i].material = MATTE;
	planes[i].color = (t_color){0.6, 0.9, 0.8, 1};

	planes[i + 1].center = (t_vec3){-3, 1, 1};
	planes[i + 1].normal = (t_vec3){1, 0, 0};
	planes[i + 1].obj_type = PLANE;
	planes[i + 1].material = MATTE;
	planes[i + 1].color = (t_color){0.6, 0.9, 0.8, 1};

	planes[i + 2].center = (t_vec3){6.8, 1, 1};
	planes[i + 2].normal = (t_vec3){-1, 0, 0};
	planes[i + 2].obj_type = PLANE;
	planes[i + 2].material = MATTE;
	planes[i + 2].color = (t_color){0.6, 0.9, 0.8, 1};
	data()->obj_len += 3;

}

void	init_data()
{
	// double focus_dist = vec3_length(vec3_subtraction((t_vec3){3, 3, -2}, (t_vec3){0, 0, 1}));
	// data()->cam_dist = 1;
	data()->obj_len = 0;
	init_spheres(data()->objects);
	init_camera(&data()->camera, 70, (t_vec3){2, 3, -5}, (t_vec3){0, 1, 0}, (t_vec3){2, 0, 1}, 1, 0);
	data()->ray.origin = data()->camera.origin;
	init_lights(data()->lights);
	init_planes(data()->objects);
}
