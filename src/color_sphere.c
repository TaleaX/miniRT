/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/09 15:19:14 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_sphere(t_sphere sphere, t_vec3 ray_origin, t_vec3 ray_direction)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = vec3_subtraction(sphere.center, ray_origin);
	a = vec3_dot(ray_direction, ray_direction);
	b = 2.0 * vec3_dot(oc, ray_direction);
	c = vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	
	discriminant = b * b - 4.0 * a * c;
	
	if (discriminant < 0.0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	// t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	// if (t2 < t1)
	// 	t1 = t2;
	return (t1);
}

t_color get_color(t_vec3 hitpos, t_vec3 center, t_color colorSphere)
{
	t_vec3	normal;
	t_color color;
	t_vec3 lightOrigin = {0, 1, 0};
	double intensity = 	0.7;
	double	n_dot_l;
	double	light = 0;
	// t_vec3 lightDir = {1, 1, 1};
	t_vec3	lightDir = vec3_subtraction(hitpos, lightOrigin);

	normal = vec3_subtraction(center, hitpos);
	vec3_normalize(&normal);
	n_dot_l = vec3_dot(lightDir, normal);
	if (n_dot_l > 0)
		light = intensity * n_dot_l / (vec3_length(normal) * vec3_length(lightDir));
	// color.r = (normal.x * 0.5 + 0.5) * light;
	// color.g = (normal.y * 0.5 + 0.5) * light;
	// color.b = (normal.z * 0.5 + 0.5) * light;
	color.r = (colorSphere.r) * light;
	color.g = (colorSphere.g) * light;
	color.b = (colorSphere.b) * light;
	color.r = (color.r > 1) ? 1 : (color.r < 0 ? 0 : color.r);
	color.g = (color.g > 1) ? 1 : (color.g < 0 ? 0 : color.g);
	color.b = (color.b > 1) ? 1 : (color.b < 0 ? 0 : color.b);
	color.a = 1;
	return (color);
}

// void	color_spheres(t_window window, t_sphere spheres[4])
// {
// 	double		t_min;
// 	t_vec3		ray_origin;
// 	t_vec3		ray_direction;
// 	t_vec3		hitpos;
// 	size_t		i;
// 	double		t_closest;

// 	i = 0;
// 	t_closest = __DBL_MAX__;
// 	init_vec3(&ray_origin, 0.0, 0.0, -2.0);
// 	init_vec3(&ray_direction, window.viewport.x, window.viewport.y, 1);
// 	vec3_normalize(&ray_direction);
// 	// while (i < 4)
// 	// {
// 	// }
// 		t_min = hit_sphere(spheres[i], ray_origin, ray_direction);
// 		if (t_min > 1 && t_min < t_closest)
// 		{
// 			// printf("in here\n");
// 			hitpos = get_hitpos(ray_origin, ray_direction, t_min);
// 			// mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_color(hitpos, spheres[i].center)); //get_rgba(sphere[i].color));//
// 			t_closest = t_min;
// 		}
// 		// ++i;
// 	if (t_closest == __DBL_MAX__)
// 		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);
// }

// void	color_sphere(t_window window, t_room room, double t_min, double *t_closest, int i)
// {
// 	t_vec3		hitpos;

// 	if (t_min >= 1 && t_min < *t_closest)
// 	{
// 		hitpos = get_hitpos(room.camera.ray_origin, room.camera.ray_direction, t_min);
// 		// mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_color(hitpos, room.spheres[i].center)); //get_rgba(sphere[i].color));//
// 		(*t_closest) = t_min;
// 	}
// }

// t_color	test(t_vec3 origin, t_vec3 dir, t_sphere spheres[4])
// {
// 	double	t;
// 	double	t_closest;
// 	int 	i;
// 	t_vec3		hitpos;
// 	t_color	color = {0, 0, 0, 1};

// 	vec3_normalize(&dir);
// 	i = 0;
// 	t_closest = __DBL_MAX__;
// 	while (i < 3)
// 	{
// 		t = hit_sphere(spheres[i], origin, dir);
// 		if (t > 1 && t < t_closest)
// 		{
// 			hitpos = get_hitpos(origin, dir, t);
// 			color = get_color(hitpos, spheres[i].center, spheres[i].color);
// 			// color = spheres[i].color;
// 			t_closest = t;
// 		}
// 		++i;

// 	}
// 	return (color);
// }