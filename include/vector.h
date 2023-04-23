/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:21 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 14:42:20 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>
# include "structs.h"

void	init_vec3(t_vec3 *v, double x, double y, double z);

double	vec3_length_squared(t_vec3 v);
double	vec3_length(t_vec3 v);
void	vec3_normalize(t_vec3 *v);
t_vec3	get_hitpos(t_vec3 ray_origin, t_vec3 ray_direction, double t);
// void	change_coords(void *self, double x, double y, double z);

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_color	color_add(t_color color1, t_color color2);
t_vec3	vec3_scalar(t_vec3 vec, double scalar);
t_color	color_mult(t_color color1, t_color color2);
t_vec3	vec3_get_normal(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_mult(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_pow(t_vec3 vec, double n);
t_color	color_add_vec(t_color color, t_vec3 vec);
t_color	color_scalar(t_color color, double scalar, double alpha);
t_vec3	vec3_scalar_subtraction(t_vec3 vec, double scalar);

//rotate
t_vec3	vec3_rotate_x(t_vec3 vec, double deg);
t_vec3	vec3_rotate_y(t_vec3 vec, double deg);
t_vec3	vec3_rotate_z(t_vec3 vec, double deg);

#endif