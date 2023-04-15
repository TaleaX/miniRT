/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:10:36 by dns               #+#    #+#             */
/*   Updated: 2023/04/06 21:19:43 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z});
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3	vec3_scalar(t_vec3 vec, double scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_vec3	vec3_get_normal(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.y * vec2.z - vec1.z * vec2.y, \
	vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x});
}

t_vec3	vec3_scalar_subtraction(t_vec3 vec, double scalar)
{
	return ((t_vec3){vec.x - scalar, vec.y - scalar, vec.z - scalar});
}

t_vec3	vec3_pow(t_vec3 vec, double n)
{
	return ((t_vec3){pow(vec.x, n), pow(vec.y, n), pow(vec.z, n)});
}