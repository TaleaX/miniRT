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

t_color	color_room(t_vec3 origin, t_vec3 dir, t_room room)
{
	double	t_min;
	double	t_closest;
	int 	i;
	t_vec3	hitpos;
	t_color	color;
	t_vec3	normal;
	t_vec3	light_ray;

	color = (t_color){0, 0, 0, 1};
	vec3_normalize(&dir);
	i = 0;
	t_closest = __DBL_MAX__;
	while (i < 4)
	{
		t_min = hit_sphere(room.spheres[i], origin, dir);
		if (t_min > 1 && t_min < t_closest)
		{
			hitpos = get_hitpos(origin, dir, t_min);
			normal = vec3_subtraction(room.spheres[i].center, hitpos);
			light_ray = get_lightRay(room.light, hitpos);
			vec3_normalize(&normal);
			vec3_normalize(&light_ray);
			// color = get_color(hitpos, room.spheres[i].center, room.spheres[i].color);
			color = get_color(calc_light(light_ray, normal, 1), room.spheres[i].color);
			// color = room.spheres[i].color;
			t_closest = t_min;
		}
		++i;

	}
	return (color);
}
