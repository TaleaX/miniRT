/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 17:42:51 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	hit_sphere(t_sphere sphere, t_vec3 ray_origin, t_vec3 ray_direction){
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec3	oc;
	double	t1;
	double	t2;

	oc = t_vec3_subtraction(sphere.center, ray_origin);
	// printf("%f %f %f\n", oc.x, oc.y, oc.z);
	a = dot_produkt(ray_direction, ray_direction);
	// b = 2.0 * (dot_produkt(ray_origin, ray_direction) - dot_produkt(sphere.center, ray_direction));
	b = 2.0 * dot_produkt(oc, ray_direction);
	// c = -2 * dot_produkt(ray_origin, sphere.center) + dot_produkt(sphere.center, sphere.center) + dot_produkt(ray_origin, ray_origin) - sphere.radius * sphere.radius;
	c = dot_produkt(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t2 < t1)
		t1 = t2;
	return (t1);
}

uint32_t get_color(t_vec3 hitpos, t_vec3 center)
{
	t_vec3	normal;
	t_color color;

	normal = t_vec3_subtraction(center, hitpos);
	normal.normalize(&normal);
	color.r = normal.x * 0.5 + 0.5;
	color.g = normal.y * 0.5 + 0.5;
	color.b = normal.z * 0.5 + 0.5;
	color.a = 1;
	return (get_rgba(color));
}

void	color_spheres(t_window window, t_sphere sphere[4])
{
	double		t_min;
	t_vec3		ray_origin;
	t_vec3		ray_direction;
	t_vec3		hitpos;
	size_t		i;
	double		t_closest;

	i = 0;
	t_closest = __DBL_MAX__;
	init_vec3(&ray_origin, 0.0, 0.0, 3.0);
	init_vec3(&ray_direction, window.coords.x, window.coords.y, -1);
	ray_direction.normalize(&ray_direction);
	while (i < 4)
	{
		t_min = hit_sphere(sphere[i], ray_origin, ray_direction);
		if (t_min > 0 && t_min < t_closest)
		{
			hitpos = get_hitpos(ray_origin, ray_direction, t_min);
			mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_color(hitpos, sphere[i].center)); //get_rgba(sphere[i].color));//
			t_closest = t_min;
		}
		++i;
	}
	if (t_closest == __DBL_MAX__)
		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);
}