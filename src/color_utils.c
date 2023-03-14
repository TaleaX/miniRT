/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 17:02:06 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	get_rgba(t_color color)
{	
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)(255.999 * color.r);
	g = (uint8_t)(255.999 * color.g);
	b = (uint8_t)(255.999 * color.b);
	a = (uint8_t)(255.999 * color.a);
	if (r > 255 || g > 255 || b > 255)
		printf("hmm\n");
	if (r < 0 || g < 0 || b < 0)
		printf("well\n");
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	get_color(double light, t_color color_obj)
{
	t_color	color;

	color.r = (color_obj.r) * light;
	color.g = (color_obj.g) * light;
	color.b = (color_obj.b) * light;
	color.r = (color.r > 1) ? 1 : (color.r < 0 ? 0 : color.r);
	color.g = (color.g > 1) ? 1 : (color.g < 0 ? 0 : color.g);
	color.b = (color.b > 1) ? 1 : (color.b < 0 ? 0 : color.b);
	color.a = 1;
	return (color);
}

// t_color get_color(t_vec3 hitpos, t_vec3 center, t_color colorSphere)
// {
// 	t_vec3	normal;
// 	t_color color;
// 	t_vec3 lightOrigin = {0, 1, 0};
// 	double intensity = 	1.0;
// 	double	n_dot_l;
// 	double	light = 0;
// 	// t_vec3 lightDir = {-1, 1, -1};
// 	t_vec3	lightDir = vec3_subtraction(hitpos, lightOrigin);

// 	normal = vec3_subtraction(center, hitpos);
// 	vec3_normalize(&normal);
// 	n_dot_l = vec3_dot(lightDir, normal);
// 	if (n_dot_l > 0)
// 		light = intensity * n_dot_l / (vec3_length(normal) * vec3_length(lightDir));
// 	// color.r = (normal.x * 0.5 + 0.5) * light;
// 	// color.g = (normal.y * 0.5 + 0.5) * light;
// 	// color.b = (normal.z * 0.5 + 0.5) * light;
// 	// color.r = (normal.x) * light;
// 	// color.g = (normal.y) * light;
// 	// color.b = (normal.z) * light;
// 	color.r = (colorSphere.r) * light;
// 	color.g = (colorSphere.g) * light;
// 	color.b = (colorSphere.b) * light;
// 	color.r = (color.r > 1) ? 1 : (color.r < 0 ? 0 : color.r);
// 	color.g = (color.g > 1) ? 1 : (color.g < 0 ? 0 : color.g);
// 	color.b = (color.b > 1) ? 1 : (color.b < 0 ? 0 : color.b);
// 	color.a = 1;
// 	return (color);
// }
