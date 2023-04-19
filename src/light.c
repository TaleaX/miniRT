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

double calc_light(t_light *lights, t_vec3 v, t_pixel px)
{
	double	n_dot_l;
	double	r_dot_v;
	double	light_var = 0.0;
	t_vec3	reflected_dir;
	t_vec3	light_dir;
	t_ray	ray;
	double	t_max;
	int		i;

	i = 0;
	while (i < data()->n_lights)
	{
		if (lights[i].type == AMBIENT)
		{
			light_var += lights[i].intensity;
		}
		else
		{

			light_dir = get_lightdir(lights[i], px.hitpoint);
			// printf("light dir %f\n", light_dir.z);
			// vec3_normalize(&light_dir);
			if (lights[i].type == POINT)
				t_max = 1;
			else if (lights[i].type == SUN)
			{
				t_max = INFINITY;
			}
			init_ray(&ray, px.hitpoint, light_dir);

			t_pixel	px_cpy = px;
			if (hit_obj(ray, &px_cpy, t_max))
			{
				++i;
				continue;
			}

			//diffuse
			n_dot_l = vec3_dot(px.normal, light_dir);
			if (n_dot_l > 0)
			{
				light_var += lights[i].intensity * n_dot_l/(vec3_length(px.normal) * vec3_length(light_dir));
			}
			//specular
			if (px.specular > 0)
			{
				reflected_dir = vec3_subtraction(light_dir, vec3_scalar(px.normal, n_dot_l * 2));
				// lp = vec3_subtraction(vec3_scalar(px.normal, n_dot_l), light_dir);
				// reflected_dir = vec3_subtraction(lp, vec3_scalar(px.normal, n_dot_l));
				r_dot_v = vec3_dot(reflected_dir, v);
				if (r_dot_v > 0)
					light_var += lights[i].intensity * pow(r_dot_v / (vec3_length(reflected_dir) * vec3_length(v)), px.specular);
			}
		}
		++i;
	}
	//if (light_var > 0.2)
	printf("light var %f\n", light_var);
	// exit(0);
	return (light_var);
}

t_color color_light(t_light *lights, t_vec3 v, t_pixel px)
{
	double	n_dot_l;
	double	r_dot_v;
	double	light_var = 0.0;
	t_vec3	reflected_dir;
	t_vec3	light_dir;
	double	t_max;
	int		i;
	t_color	color = (t_color){0,0,0,1};
	t_color	diffuse = (t_color){0,0,0,1};
	t_color ambient = (t_color){0,0,0,1};

	i = 0;
	while (i < data()->n_lights)
	{
		if (lights[i].type == AMBIENT)
			ambient = color_scalar(lights[i].color, lights[i].intensity, 1);
		else
		{

			light_dir = get_lightdir(lights[i], px.hitpoint);
			if (lights[i].type == POINT)
				t_max = 1;
			else if (lights[i].type == SUN)
				t_max = INFINITY;
			if (check_shadow(px, light_dir, t_max))
			{
				++i;
				continue;
			}

			//diffuse
			n_dot_l = vec3_dot(px.normal, light_dir);
			if (n_dot_l > 0)
			{
				light_var = lights[i].intensity * n_dot_l/(vec3_length(px.normal) * vec3_length(light_dir));
				diffuse = color_add(diffuse, color_scalar(lights[i].color, light_var, 1));
			}
			if (px.specular > 0)
			{
				reflected_dir = vec3_subtraction(light_dir, vec3_scalar(px.normal, n_dot_l * 2));
				r_dot_v = vec3_dot(reflected_dir, v);
				if (r_dot_v > 0)
				{
					light_var = lights[i].intensity * pow(r_dot_v / (vec3_length(reflected_dir) * vec3_length(v)), px.specular);
					diffuse = color_add(diffuse, color_scalar(lights[i].color, light_var, 1));
				}
			}
			
		}
		++i;
	}
	color = color_add(ambient, diffuse);
	// printf("color %f %f %f\n", color.r, color.g, color.b);
	return (color);
}
