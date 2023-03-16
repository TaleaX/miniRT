/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:21 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/14 23:22:43 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>

typedef struct s_v2		t_vec2;
typedef struct s_v3		t_vec3;
typedef struct s_color	t_color;

void	init_vec3(t_vec3 *v, double x, double y, double z);

double	vec3_length(t_vec3 v);
void	vec3_normalize(t_vec3 *v);
t_vec3	get_hitpos(t_vec3 ray_origin, t_vec3 ray_direction, double t);
// void	change_coords(void *self, double x, double y, double z);

struct s_v2 {
	double	x;
	double	y;
};

struct s_v3 {
	double	x;
	double	y;
	double	z;
};

struct s_color {
	double	r;
	double	g;
	double	b;
	double	a;
};

double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_color	color_add(t_color color1, t_color color2);
t_vec3	vec3_scalar(t_vec3 vec, double scalar);
t_color	color_mult(t_color color1, t_color color2);

#endif