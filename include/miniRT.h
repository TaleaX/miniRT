/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/16 13:31:46 by tdehne           ###   ########.fr       */
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
// # include "tinux.h"

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
void	init_camera(t_camera *camera, t_vec3 vup);
bool	hit_finite(t_ray ray, t_obj cylinder, double t);
double	hit_sphere(t_obj sphere, t_ray ray);
double	hit_cylinder(t_obj cylinder, t_ray ray);
double	hit_plane(t_obj plane, t_ray ray);
int		error_handling(int error);

#endif