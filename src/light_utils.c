/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:35:16 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 14:35:50 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	get_lightdir(t_light light, t_vec3 hit_pos)
{
	if (light.type == SUN)
	{
		return (light.ray.direction);
	}
	return (vec3_subtraction(hit_pos, light.ray.origin));
}

bool	check_shadow(t_pixel px, t_vec3	light_dir, double t_max)
{
	t_pixel	px_cpy;

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
