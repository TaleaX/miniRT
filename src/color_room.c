/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:01:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/30 15:43:37 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	power(double num)
{
	return (num * num);
}

// t_color	color_room(t_ray ray, t_vec2 coord, int depth)
// {
// 	t_color	color;
// 	t_vec3	target;
// 	t_vec3	random_p;
// 	t_vec3	reflected_dir;
// 	t_ray	cur_ray;
// 	t_color	cur_attenuation = {1, 1, 1, 1};
// 	t_pixel	*px;

// 	px = &(data()->px[coord.y][coord.x]);
	
// 	// if (depth <= 0.0)
// 	// 	return ((t_color){0, 0, 0, 1});


// 		for (int i = 0; i < 50; i++)
// 		{
// 			if (hit_obj(ray, px))
// 			{
// 				if (px->material == MATTE)
// 				{
// 					// random_p = random_in_usphere();
// 					vec3_normalize(&px->normal);
// 					// vec3_normalize(&random_p);
// 					// px->hitpoint = vec3_add(px->hitpoint, vec3_scalar(px->normal, 0.01));
// 					target = vec3_add(px->hitpoint, random_in_hemisphere(px->normal));
// 					ray = new_ray(px->hitpoint, vec3_subtraction(px->hitpoint, target));
// 					cur_attenuation = px->color;
// 					// color = color_scalar(color_room(r, coord, depth-1), 0.5, 1);
// 					// return (color);

// 					// return (color_mult(color, px->color));
// 				}
// 			} else {
// 				vec3_normalize(&ray.direction);
// 				double t = 0.5*(ray.direction.y + 1.0);
// 				t_color colorStart = (t_color){1, 1, 1, 1};
// 				colorStart = color_scalar(colorStart, 1.0 - t , 1);
// 				t_color c = color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1));
// 				// return (color_scalar(c, cur_attenuation, 1));
// 				return (color_mult(c, cur_attenuation));
// 				// return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
// 			}
// 		}
// 	return ((t_color){0, 0, 0, 1});
// }


bool	scatter(t_ray ray, t_ray *scattered, t_color *attenuation, t_pixel *px)
{
	t_vec3	target;
	// t_vec3	random_p;
	t_vec3	reflected_dir;
	t_vec3	scattered_dir;
	bool	ref = false;

	vec3_normalize(&px->normal);
	if (px->material == MATTE)
	{
		// random_p = random_in_usphere();
		// vec3_normalize(&random_p);

		target = vec3_add(px->hitpoint, random_in_hemisphere(px->normal));
		scattered_dir = vec3_subtraction(px->hitpoint, target);
		// scattered_dir = vec3_add(px->normal, random_in_usphere());
		// t_ray scattered = new_ray(px->hitpoint, vec3_subtraction(px->hitpoint, target));
		if (near_zero(scattered_dir))
			scattered_dir = px->normal;
		*scattered = new_ray(px->hitpoint, scattered_dir);
		*attenuation = px->color;
		// color = color_scalar(color_room(r, coord, depth-1), 0.5, 1);
		ref = true;

		// return (color_mult(color, px->color));
	}
	if (px->material == MIRROR)
	{
		printf("in here\n");
		// vec3_normalize(&ray.direction);
		reflected_dir = reflected_direction(ray.direction, px->normal);
		// t_ray reflected_ray = new_ray(px->hitpoint, vec3_add(reflected_dir, vec3_scalar(random_in_usphere(), px->fuzz)));
		*scattered = new_ray(px->hitpoint, vec3_add(reflected_dir, vec3_scalar(random_in_usphere(), px->fuzz)));
		*attenuation = px->color;
		ref = (vec3_dot(scattered->direction, px->normal) > 0) ? true : false;
	}
	return (ref);
		// if (ref)
		// {
		// 	t_color attenuation = (t_color){0.5, 0.0, 0.8, 1};
		// 	color = color_room(reflected_ray, coord, depth-1);
		// 	t_vec3 v = vec3_scalar(ray.direction, -1);
		// 	return (get_color(calc_light(data()->light, v, *px), color_mult(color, attenuation)));
		// 	// return (color_mult(color, px->color));
		// }
		// return ((t_color){0, 0, 0, 1});
}
t_color	color_room(t_ray ray, t_vec2 coord, int depth)
{
	// t_color	color;
	// t_vec3	target;
	// t_vec3	random_p;
	// t_vec3	reflected_dir;
	t_color	attenuation;
	t_ray	scattered;
	t_pixel	*px;

	px = &(data()->px[coord.y][coord.x]);
	vec3_normalize(&ray.direction);
	if (depth <= 0.0)
		return ((t_color){0, 0, 0, 1});
	if (hit_obj(ray, px))
	{
			if (scatter(ray, &scattered, &attenuation, px))
			{
				return (color_mult(attenuation, color_room(scattered, coord, depth - 1)));
			}
			return ((t_color){0, 0, 0, 1});
	}

    double t = 0.5*(ray.direction.y + 1.0);
	t_color colorStart = (t_color){1, 1, 1, 1};
	colorStart = color_scalar(colorStart, 1.0 - t , 1);
	return (color_add(colorStart, color_scalar((t_color){0.5, 0.7, 1.0, 1.0}, t, 1)));
}

// random_p = random_in_usphere();
// // light_ray = get_lightRay(room.light, rec.hitpos);
// // exit(0);
// vec3_normalize(&px->normal);
// vec3_normalize(&random_p);
// // vec3_normalize(&light_ray);
// // color = get_color(calc_light(light_ray, rec.normal, 0.5), room.spheres[s].color);
// // target = vec3_add(vec3_add(px->hitpoint, px->normal), random_p);
// target = vec3_add(px->hitpoint, random_in_hemisphere(px->normal));
// t_ray r = new_ray(px->hitpoint, vec3_subtraction(px->hitpoint, target));
// color = color_room(r, coord, depth-1);
// // return (color_scalar(color, 0.5, 1));
// // t_vec3 v = vec3_scalar(ray.direction, -1); //get_color(calc_light(data()->light, v, *px), 
// // return (get_color(calc_light(data()->light, v, *px), px->color)); 
// return (color_mult(color, px->color));