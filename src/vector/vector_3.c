/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:14:05 by dns               #+#    #+#             */
/*   Updated: 2023/04/11 14:45:54 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_mult(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

t_color	color_add(t_color color1, t_color color2)
{
	return ((t_color){color1.r + color2.r, color1.g \
	+ color2.g, color1.b + color2.b, color2.a});
}

t_color	color_scalar(t_color color, double scalar, double alpha)
{
	return ((t_color){color.r * scalar, color.g \
	* scalar, color.b * scalar, color.a * alpha});
}

t_color	color_add_vec(t_color color, t_vec3 vec)
{
	return ((t_color){color.r + vec.x, color.g + vec.y, color.b + vec.z, 1});
}

t_color	color_mult(t_color color1, t_color color2)
{
	return ((t_color){color1.r * color2.r, color1.g \
	* color2.g, color1.b * color2.b, color1.a * color2.a});
}
