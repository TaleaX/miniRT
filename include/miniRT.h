/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/13 17:43:13 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <pthread.h>

# include "../get_next_line/get_next_line.h"
# include "vector.h"
# include "structs.h"
# include "color.h"
# include "calc.h"
# include "parser.h"
# include "tinux.h"

# define RATIO 1.5f

void	init_hit_rec(t_hit_rec *hit_rec, \
t_vec3 hitpos, t_vec3 normal, double t);
bool	hit_obj(t_ray ray, t_pixel *px, double t_max);

//init
void	init_spheres(t_obj *spheres);
void	init_color(t_color *color, double r, double g, double b);
void	init_plane(t_plane *plane);
void	init_room(t_room *room);
void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction);
t_ray	new_ray(t_vec3 origin, t_vec3 direction);
t_ray	get_ray(double h, double v);
t_color	sampling(t_vec2 coord);
void	init_data(void);
t_vec3	reflected_direction(t_vec3 lightRay, t_vec3 normal);

int		error_handling(int error);

#endif