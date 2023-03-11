/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 17:01:53 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t get_color2(t_vec3 hitpos, t_vec3 center)
{
	t_vec3	normal;
	t_color color;

	normal = vec3_subtraction(center, hitpos);
	vec3_normalize(&normal);
	color.r = normal.x * 0.5 + 0.5;
	color.g = normal.y;// * 0.5 + 0.5;
	color.b = normal.z * 0.5 + 0.5;
	color.a = 1;
	return (get_rgba(color));
}


uint32_t get_color_t(double t)
{
	t_color color;
	double	t_max = 100;

	color.r = (t - 0.9*t) / t_max;// * 0.5 + 0.5;
	color.g = (t - 0.9*t) / t_max;// * 0.5 + 0.5;
	color.b = t / t_max + 0.05;// * 0.5 + 0.5;
	color.a = 1;
	if (color.r >= 1 || color.g >= 1)
		printf("r %f g %f b %f\n", color.r, color.g, color.b);
	color.r =  (color.r > 1) ? 1: (color.r < 0 ? 0 : color.r);
	color.g =  (color.g > 1) ? 1: (color.g < 0 ? 0 : color.g);
	color.b =  (color.b > 1) ? 1: (color.b < 0 ? 0 : color.b);
	return (get_rgba(color));
}

// void	color_planeX(t_window window, t_plane plane)
// {
// 	t_vec3		ray_origin;
// 	t_vec3		ray_direction;
// 	t_vec3		hitpos;
// 	double		t;

// 	init_vec3(&ray_origin, 0.0, 5.0, 0.0);
// 	init_vec3(&ray_direction, window.coords.x, window.coords.y, 1);
// 	vec3_normalize(&ray_direction);
// 	t = hit_plane(plane, ray_origin, ray_direction);
// 	if (t > 0)
// 	{
// 		hitpos = get_hitpos(ray_origin, ray_direction, t);
// 		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_color_t(t));//get_color2(hitpos, plane.c));
// 	}
// 	else {
// 		t_color color = {0.8, 0.8, 1, 1};
// 		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_rgba(color));
// 	}
// }
