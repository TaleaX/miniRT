/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:01:39 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 20:01:41 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_rotate_x(t_vec3 vec, double deg)
{
	double	rad;
	t_vec3	rotated;

	rad = degree_to_radian(deg);
	rotated.x = vec.x;
	rotated.y = vec.y * cosf(rad) - vec.z * sinf(rad);
	rotated.z = vec.y * sinf(rad) + vec.z * cosf(rad);
	return (rotated);
}

t_vec3	vec3_rotate_y(t_vec3 vec, double deg)
{
	double	rad;
	t_vec3	rotated;

	rad = degree_to_radian(deg);
	rotated.x = vec.x * cosf(rad) + vec.z * sinf(rad);
	rotated.y = vec.y;
	rotated.z = -vec.x * sinf(rad) + vec.z * cosf(rad);
	return (rotated);
}

t_vec3	vec3_rotate_z(t_vec3 vec, double deg)
{
	double	rad;
	t_vec3	rotated;

	rad = degree_to_radian(deg);
	rotated.x = vec.x * cosf(rad) - vec.y * sinf(rad);
	rotated.y = vec.x * sinf(rad) + vec.y * cosf(rad);
	rotated.z = vec.z;
	return (rotated);
}
