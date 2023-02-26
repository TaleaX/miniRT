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
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

void	color_sphere(t_window window, t_sphere sphere)
{
	double		t;
	t_color		color;
	t_vec3		ray_origin = {0.0, 0.0, 1.0};
	t_vec3		ray_direction = {window.coords.x, window.coords.y, -1};

	t = hit_sphere(sphere, ray_origin, ray_direction);
	if (t >= 0.0) {
		// printf("%f\n",t);
		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x00ff00ff);
	} else {
		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);
	}
}