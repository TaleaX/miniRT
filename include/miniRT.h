/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/30 16:43:36 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# include <parser.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <time.h>
# include <fcntl.h>

# include "../get_next_line/get_next_line.h"
# include "vector.h"
# include "structs.h"
# include "color.h"
# include "calc.h"
# include "parser.h"
# include "tinux.h"

# define RATIO 1.5f
// # define VH 1.0f

//(int) (HEIGHT * RATIO)
// # define VW 1.0f
//(double)(VH * RATIO)


// void	color_spheres(t_window window, t_sphere spheres[4]);
// void	color_plane(t_window window, t_room room, double t_min, double *t_closest, int i);

// void	color_sphere(t_window window, t_room room, double t_min, double *t_closest, int i);
// void	color_planeX(t_window window, t_plane plane);

// void	init_window(t_window *window, mlx_image_t *g_img, double height, double width);
void	init_hit_rec(t_hit_rec *hit_rec, t_vec3 hitpos, t_vec3 normal, double t);
bool	hit_obj(t_ray ray, t_pixel *px, double t_max);
// t_color	sampling(t_window window, t_room room);

//init
void	init_spheres(t_obj* spheres);
void	init_color(t_color *color, double r, double g, double b);
void	init_plane(t_plane* plane);
void	init_room(t_room *room);
void	init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction);
t_ray	new_ray(t_vec3 origin, t_vec3 direction);
t_ray	get_ray();
t_color	sampling(t_vec2 coord);
void	init_data();
t_vec3	reflected_direction(t_vec3 lightRay, t_vec3 normal);

int	error_handling(int error);

#endif