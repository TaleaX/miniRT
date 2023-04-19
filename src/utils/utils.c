/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:48:46 by dns               #+#    #+#             */
/*   Updated: 2023/04/13 17:42:30 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	random_double(void)
{
	return ((double)rand() / (double)((double)RAND_MAX + 1.0));
}

double	random_min_max(double min, double max)
{
	return (random_double() * (max - min) + min);
}

t_vec3	random_in_usphere(void)
{
	t_vec3	random_point;

	while (true)
	{
		init_vec3(&random_point, random_min_max(-1, 1), \
		random_min_max(-1, 1), random_min_max(-1, 1));
		if (vec3_length_squared(random_point) >= 1)
			continue ;
		return (random_point);
	}
}

t_vec3	random_in_udisk(void)
{
	t_vec3	random_point;

	while (true)
	{
		init_vec3(&random_point, random_min_max(-1, 1), \
		random_min_max(-1, 1), 0);
		if (vec3_length_squared(random_point) >= 1)
			continue ;
		return (random_point);
	}
}

t_vec3	random_in_hemisphere(t_vec3 normal)
{
	t_vec3	in_usphere;

	in_usphere = random_in_usphere();
	if (vec3_dot(in_usphere, normal) > 0.0)
		return (in_usphere);
	return (vec3_scalar(in_usphere, -1));
}
