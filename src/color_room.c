/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 05:14:27 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



t_color	color_room(t_ray ray, t_room room, int depth)
{
	t_color	color;
	t_vec3	target;
	t_vec3	random_p;
	t_hit_rec rec;

	// vec3_normalize(&ray.direction);
	if (depth <= 0.0)
		return ((t_color){0, 0, 0, 1});
	if (hit_obj(&rec, ray, room))
	{
		random_p = random_in_usphere();
		// light_ray = get_lightRay(room.light, rec.hitpos);
		// exit(0);
		vec3_normalize(&rec.normal);
		vec3_normalize(&random_p);
		// vec3_normalize(&light_ray);
		// color = get_color(calc_light(light_ray, rec.normal, 0.5), room.spheres[s].color);
		target = vec3_add(vec3_add(rec.hitpos, rec.normal), random_p);
		t_ray r = new_ray(rec.hitpos, vec3_subtraction(rec.hitpos, target));
		// printf("%f %f\n", r.direction.x, r.direction.y);
		return (color_scalar(color_room(r, room, depth-1), 0.5, 1));
        // return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
		// return (color_scalar(color_add_vec((t_color){1, 1, 1, 1}, rec.normal), 0.5, 1));
	}

    double t = 0.5*(ray.direction.y + 1.0);
	t_color colorStart = (t_color){1, 1, 1, 1};
	colorStart = color_scalar(colorStart, 1.0 - t , 1);
	return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
}
