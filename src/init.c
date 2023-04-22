/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 16:05:03 by dantonik         ###   ########.fr       */
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

void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction)
{
	ray->origin = origin;
	ray->direction = direction;
}

void	init_camera(t_camera *camera, t_vec3 vup)
{
	double	hfov_rad;
	double	viewport_width;
	double	viewport_height;

	hfov_rad = degree_to_radian(camera->hfov);
	camera->w = camera->orientation;
	vec3_normalize(&camera->w);
	camera->u = vec3_get_normal(vup, camera->w);
	vec3_normalize(&camera->u);
	camera->v = vec3_get_normal(camera->w, camera->u);
	viewport_width = 2 * tanf(hfov_rad / 2.0) * VIEWPORT_DIST;
	viewport_height = viewport_width / data()->aspect_ratio;
	camera->viewport_vertical = vec3_scalar(camera->v, viewport_height);
	camera->viewport_horizontal = vec3_scalar(camera->u, viewport_width);
	camera->lower_left_corner = vec3_subtraction(\
		vec3_scalar(camera->viewport_horizontal, 0.5), camera->origin);
	camera->lower_left_corner = vec3_subtraction(\
		vec3_scalar(camera->viewport_vertical, 0.5), camera->lower_left_corner);
	camera->lower_left_corner = vec3_add(camera->w, camera->lower_left_corner);
}
