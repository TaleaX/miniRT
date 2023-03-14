/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 17:02:00 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color_room(t_vec3 origin, t_vec3 dir, t_room room, int depth)
{
	double	t_min;
	double	t_closest;
	int 	i;
	t_vec3	hitpos;
	t_color	color;
	t_vec3	normal;
	t_vec3	light_ray;
	t_vec3	target;
	t_vec3	random_p;
	int		s;

	vec3_normalize(&dir);
	i = 0;
	t_closest = __DBL_MAX__;
	if (depth <= 0.0)
		return ((t_color){0, 0, 0, 1});
	while (i < 4)
	{
		t_min = hit_sphere(room.spheres[i], origin, dir);
		if (t_min > 1 && t_min < t_closest)
		{
			hitpos = get_hitpos(origin, dir, t_min);
			s = i;
			t_closest = t_min;
		}
		++i;

	}
	if (t_closest != __DBL_MAX__) {
		normal = vec3_subtraction(room.spheres[s].center, hitpos);
		random_p = random_in_usphere();
		vec3_normalize(&normal);
		// vec3_normalize(&light_ray);
		// color = get_color(hitpos, room.spheres[i].center, room.spheres[i].color);
		// color = room.spheres[i].color;
		// light_ray = get_lightRay(room.light, hitpos);
		init_vec3(&target, hitpos.x + normal.x + random_p.x, hitpos.y + normal.y + random_p.y, hitpos.z + normal.z + random_p.z);

		// color = get_color(calc_light(light_ray, normal, 1), room.spheres[s].color);
		// return (color);
		return (color_scalar(color_room(hitpos, vec3_subtraction(hitpos, target), room, depth - 1), 0.5, 1));
	}
	vec3_normalize(&dir);
    double t = 0.5*(dir.y + 1.0);
	t_color colorStart = (t_color){1, 1, 1, 1};
	colorStart = color_scalar(colorStart, 1.0 - t , 1);
	// printf("r %f g %f b %f a %f\n", color.r, color.g, color.b, color.a);
	return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
}
