/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:02:00 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/18 17:36:14 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	get_lightdir(t_light light, t_vec3 hit_pos)
{
	if (light.type == SUN)
	{
		return (light.ray.direction);
	}
	return(vec3_subtraction(hit_pos, light.ray.origin));
}


bool	check_shadow(t_pixel px, t_vec3	light_dir, double t_max)
{
	t_pixel	px_cpy;

	px_cpy;
	if (hit_obj(new_ray(px.hitpoint, light_dir), &px_cpy, t_max))
	{
		return (true);
	}
	return (false);
}

double	get_t_max(t_light light)
{
	if (light.type == POINT)
		return (1);
	else if (light.type == SUN)
		return (INFINITY);
	return (0);
}

t_color	diffuse_light(t_light light, t_pixel px, t_color diffuse, t_vec3 light_dir)
{
	double	n_dot_l;
	double	light_var;
	double	r_dot_v;
	t_vec3	reflected_dir;
	t_vec3	v;

	//diffuse only
	n_dot_l = vec3_dot(px.normal, light_dir);
	if (n_dot_l > 0)
	{
		light_var = light.intensity * n_dot_l / (vec3_length(px.normal) * vec3_length(light_dir));
		diffuse = color_add(diffuse, color_scalar(light.color, light_var, 1));
	}

	//specular
	if (px.specular > 0)
	{
		reflected_dir = vec3_subtraction(light_dir, vec3_scalar(px.normal, n_dot_l * 2));
		v = vec3_scalar(px.ray.direction, -1);
		r_dot_v = vec3_dot(reflected_dir, v);
		if (r_dot_v > 0)
		{
			light_var = light.intensity * pow(r_dot_v / (vec3_length(reflected_dir) * vec3_length(v)), px.specular);
			diffuse = color_add(diffuse, color_scalar(light.color, light_var, 1));
		}
	}
	return (diffuse);
}

t_color color_light(t_light *lights, t_pixel px)
{
	t_vec3	light_dir;
	t_color	color;
	t_color	diffuse;
	int		i;

	diffuse = (t_color){0,0,0,1};
	color = (t_color){0,0,0,1};
	i = 0;
	while (i < data()->n_lights)
	{
		if (lights[i].type == AMBIENT)
			color = color_scalar(lights[i].color, lights[i].intensity, 1);
		else
		{

			light_dir = get_lightdir(lights[i], px.hitpoint);
			//shadows
			if (check_shadow(px, light_dir, get_t_max(lights[i])))
			{
				++i;
				continue;
			}
			//diffuse
			diffuse = diffuse_light(lights[i], px, diffuse, light_dir);
		}
		++i;
	}
	color = color_add(color, diffuse);
	return (color);
}
