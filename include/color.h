/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:01:37 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/11 15:53:56 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# include <stdlib.h>
# include <stdint.h>
# include "structs.h"

uint32_t	get_rgba(t_color color);
uint32_t	get_color_t(double t);
t_color		get_color(double light, t_color color_obj);
t_color		color_add_vec(t_color color, t_vec3 vec);
t_color		color_scalar(t_color color, double scalar, double alpha);
t_color		color_light(t_light *lights, t_vec3 v, t_pixel px);

#endif