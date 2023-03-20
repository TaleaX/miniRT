/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 06:33:49 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	power(double num)
{
	return (num * num);
}

// t_color	sampling(t_window window, t_room room)
// {
// 	t_color color;
// 	int		s;
// 	int		samples = 20;
// 	double	scale = (double)(1.0 / samples);
// 	t_hit_rec rec;

// 	s = 0;
// 	room.camera.ray.direction.x = ((window.x) * VW / (double)(WIDTH -1) - (VW / 2.0)) - room.camera.ray.origin.x;
// 	room.camera.ray.direction.y = (((window.y) * VH / (double)(HEIGHT- 1) - (VH/ 2.0)) * -1) - room.camera.ray.origin.y;
// 	if (!hit_obj(&rec, room.camera.ray, room))
// 	{
// 		double t = 0.5*(room.camera.ray.direction.y + 1.0);
// 		t_color colorStart = (t_color){1, 1, 1, 1};
// 		colorStart = color_scalar(colorStart, 1.0 - t , 1);
// 		return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
// 	}
// 	color = (t_color){0, 0, 0, 1};
// 	// printf("in here\n");
// 	// double dist = power(rec.hitpos.x - rec.center.x) + power(rec.hitpos.y - rec.center.y) + power(rec.hitpos.z - rec.center.z);

// 	// if (dist != power(rec.radius) && rec.material != MATTE)
// 	// {
// 	// 	color = color_add(color, color_room(room.camera.ray, room, 40));
// 	// 	return (color);
// 	// }
// 	// room.camera.ray.direction.x = ((window.x + 0.1) * VW / (double)(WIDTH -1) - (VW / 2.0)) - room.camera.ray.origin.x;
// 	// room.camera.ray.direction.y = (((window.y + 0.1) * VH / (double)(HEIGHT- 1) - (VH/ 2.0)) * -1) - room.camera.ray.origin.y;
// 	// if (hit_obj(&rec, room.camera.ray, room))
// 	// {
// 	// 	color = color_add(color, color_room(room.camera.ray, room, 40));
// 	// 	return (color);
// 	// }
// 	while (s < samples)
// 	{
// 		room.camera.ray.direction.x = ((window.x + random_double()) * VW / (double)(WIDTH -1) - (VW / 2.0)) - room.camera.ray.origin.x;
// 		room.camera.ray.direction.y = (((window.y + random_double()) * VH / (double)(HEIGHT- 1) - (VH/ 2.0)) * -1) - room.camera.ray.origin.y;
// 		color = color_add(color, color_room(room.camera.ray, room, 40));
// 		// printf("%f %f %f\n", color.r, color.g, color.b);
// 		++s;
// 	}
// 	color.r = sqrt(scale * color.r);
// 	color.g = sqrt(scale * color.g);
// 	color.b = sqrt(scale * color.b);
// 	return (color);
// }

t_color	color_room(t_ray ray, t_vec2 coord, int depth)
{
	t_color	color;
	t_vec3	target;
	t_vec3	random_p;
	t_vec3	reflected_dir;
	t_pixel	*px;

	px = &(data()->px[coord.y][coord.x]);
	// vec3_normalize(&ray.direction);
	if (depth <= 0.0)
		return ((t_color){0, 0, 0, 1});
	if (hit_obj(ray, px))
	{
		if (px->material == MATTE)
		{
			random_p = random_in_usphere();
			// light_ray = get_lightRay(room.light, rec.hitpos);
			// exit(0);
			vec3_normalize(&px->normal);
			vec3_normalize(&random_p);
			// printf("obj %f %f %f\n", data()->objects[px->obj_id].center.x, data()->objects[px->obj_id].center.y, data()->objects[px->obj_id].center.z);
			// printf("normal %f %f %f\n", px->normal.x, px->normal.y, px->normal.z);
			// vec3_normalize(&light_ray);
			// color = get_color(calc_light(light_ray, rec.normal, 0.5), room.spheres[s].color);
			// target = vec3_add(vec3_add(rec.hitpos, rec.normal), random_p);
			target = vec3_add(px->hitpoint, random_in_hemisphere(px->normal));
			t_ray r = new_ray(px->hitpoint, vec3_subtraction(px->hitpoint, target));
			color = color_room(r, coord, depth-1);
			return (color_scalar(color, 0.5, 1));
		}
		if (px->material == MIRROR)
		{
			vec3_normalize(&ray.direction);
			vec3_normalize(&px->normal);
			reflected_dir = reflected_direction(ray.direction, px->normal);
			t_ray reflected_ray = new_ray(px->hitpoint, reflected_dir);
			bool ref = (vec3_dot(reflected_ray.direction, px->normal) > 0) ? true : false;
			if (ref)
			{
				color = color_room(reflected_ray, coord, depth-1);
				t_color attenuation = (t_color){0.5, 0, 0.8, 1};
				return (color_mult(color, attenuation));
			}
			return ((t_color){0, 0, 0, 1});
		}
	}

    double t = 0.5*(ray.direction.y + 1.0);
	t_color colorStart = (t_color){1, 1, 1, 1};
	colorStart = color_scalar(colorStart, 1.0 - t , 1);
	return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
}
