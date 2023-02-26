/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:14:58 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 17:14:04 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
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
	return (r << 24 | g << 16 | b << 8 | a);
}
