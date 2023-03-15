/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 02:47:40 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	clamp(double value, double min, double max)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

uint32_t	get_rgba(t_color color)
{	
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)(255.999 * clamp(color.r, 0, 1));
	g = (uint8_t)(255.999 * clamp(color.g, 0, 1));
	b = (uint8_t)(255.999 * clamp(color.b, 0, 1));
	a = (uint8_t)(255.999 * clamp(color.a, 0, 1));
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	get_color(double light, t_color color_obj)
{
	t_color	color;

	// color_obj.r = color_obj.r * 0.5 + 0.5;
	// color_obj.g = color_obj.g * 0.5 + 0.5;
	// color_obj.b = color_obj.b * 0.5 + 0.5;
	color.r = (color_obj.r) * light;
	color.g = (color_obj.g) * light;
	color.b = (color_obj.b) * light;
	// color.r = (color.r > 1) ? 1 : (color.r < 0 ? 0 : color.r);
	// color.g = (color.g > 1) ? 1 : (color.g < 0 ? 0 : color.g);
	// color.b = (color.b > 1) ? 1 : (color.b < 0 ? 0 : color.b);
	color.a = 1;
	return (color);
}
