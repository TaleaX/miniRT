/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:02:00 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 05:06:31 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_lightDir(t_light light, t_vec3 hit_pos)
{
	if (light.type == SUN)
		return (light.ray.direction);
	return(vec3_subtraction(hit_pos, light.ray.origin));
}

// double calc_light(t_vec3 light_ray, t_vec3 normal, double intensity)
// {
// 	double	n_dot_l;
// 	double	light = 0.0;

// 	n_dot_l = vec3_dot(light_ray, normal);
// 	if (n_dot_l > 0)
// 		light = intensity * n_dot_l / (vec3_length(normal) * vec3_length(light_ray));
// 	return (light);
// }

double calc_light(t_light light, t_vec3 v, t_pixel px)
{
	double	n_dot_l;
	double	r_dot_v;
	double	light_var = 0.0;
	t_vec3	reflected_direction;
	t_vec3	light_dir;


	light_dir = get_lightDir(light, px.hitpoint);
	vec3_normalize(&light_dir);

	n_dot_l = vec3_dot(px.normal, light_dir);
	if (n_dot_l > 0)
	{
		light_var += light.intensity * n_dot_l/(vec3_length(px.normal) * vec3_length(light_dir));
	}
	if (px.specular > 0)
	{
		reflected_direction = vec3_subtraction(light_dir, vec3_scalar(px.normal, n_dot_l * 2));
		r_dot_v = vec3_dot(reflected_direction, v);
		if (r_dot_v > 0)
			light_var += light.intensity * pow(r_dot_v / (vec3_length(reflected_direction) * vec3_length(v)), px.specular);
	}
	return (light_var);
}