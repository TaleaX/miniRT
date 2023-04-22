/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:02:00 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 15:22:32 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	specular_light(t_light l, t_pixel px, double n_dot_l, t_vec3 ld)
{
	t_vec3	v;
	t_vec3	reflected_dir;
	double	r_dot_v;
	double	light_var;

	light_var = -1;
	if (px.specular > 0)
	{
		reflected_dir = vec3_subtraction(ld, \
		vec3_scalar(px.normal, n_dot_l * 2));
		v = vec3_scalar(px.ray.direction, -1);
		r_dot_v = vec3_dot(reflected_dir, v);
		if (r_dot_v > 0)
		{
			light_var = l.intensity * pow(r_dot_v / \
			(vec3_length(reflected_dir) * vec3_length(v)), px.specular);
			return (light_var);
		}
	}
	return (light_var);
}

//specular
t_color	diffuse_light(t_light l, t_pixel px, t_color d, t_vec3 ld)
{
	double	n_dot_l;
	double	light_var;

	n_dot_l = vec3_dot(px.normal, ld);
	if (n_dot_l > 0)
	{
		light_var = l.intensity * n_dot_l / \
		(vec3_length(px.normal) * vec3_length(ld));
		d = color_add(d, color_scalar(l.color, light_var, 1));
	}
	light_var = specular_light(l, px, n_dot_l, ld);
	if (light_var != -1)
		d = color_add(d, color_scalar(l.color, light_var, 1));
	return (d);
}

t_color	color_light(t_light *lights, t_pixel px)
{
	t_vec3	light_dir;
	t_color	color;
	t_color	diffuse;
	int		i;

	diffuse = (t_color){0, 0, 0, 1};
	color = (t_color){0, 0, 0, 1};
	i = 0;
	while ((size_t)i < data()->n_lights)
	{
		if (lights[i].type == AMBIENT)
			color = color_scalar(lights[i].color, lights[i].intensity, 1);
		else
		{
			light_dir = get_lightdir(lights[i], px.hitpoint);
			if (check_shadow(px, light_dir, get_t_max(lights[i])))
			{
				++i;
				continue ;
			}
			diffuse = diffuse_light(lights[i], px, diffuse, light_dir);
		}
		++i;
	}
	return (color_add(color, diffuse));
}
