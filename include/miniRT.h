/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 20:23:37 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
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
# include "parser.h"
// # include "tinux.h"

bool		hit_obj(t_ray ray, t_pixel *px, double t_max);

//init
void		init_spheres(t_obj *spheres);
void		init_color(t_color *color, double r, double g, double b);
void		init_plane(t_plane *plane);
void		init_room(t_room *room);
void		init_ray(t_ray *ray, t_vec3 origin, t_vec3 direction);
void		init_data(void);

// t_color	sampling(t_vec2 coord);

//init
void		init_camera(t_camera *camera, t_vec3 vup);

//utils
bool		near_zero(t_vec3 vec);
double		degree_to_radian(double degree);
t_vec3		random_in_udisk(void);
t_vec3		random_in_hemisphere(t_vec3 normal);
double		random_double(void);
double		random_min_max(double min, double max);
t_vec3		random_in_usphere(void);
t_vec3		reflected_direction(t_vec3 lightRay, t_vec3 normal);
void		set_face_normal(t_ray ray, t_vec3 *outward_normal);
t_ray		get_ray(double h, double v);

//utils create
t_ray		new_ray(t_vec3 origin, t_vec3 direction);

//hit
bool		hit_finite(t_ray ray, t_obj cylinder, double t);
double		hit_sphere(t_obj sphere, t_ray ray);
double		hit_cylinder(t_obj cylinder, t_ray ray);
double		hit_plane(t_obj plane, t_ray ray);

//color
uint32_t	get_rgba(t_color color);
uint32_t	get_color_t(double t);
t_color		get_color(double light, t_color color_obj);

//color room
t_color		color_room(t_ray ray, t_vec2 coord, int depth);

//light
t_color		color_light(t_light *lights, t_pixel px);
t_vec3		get_lightdir(t_light light, t_vec3 hit_pos);
bool		check_shadow(t_pixel px, t_vec3	light_dir, double t_max);
double		get_t_max(t_light light);

int			error_handling(int error);

void		ft_error(void);
void		hook(void *param);
int			finish_program(mlx_t *mlx);
void		init_ratios(void);

//keyhooks utils
void		move_cylinder(t_move move);
void		rotate_cylinder(t_rot_axis axis);
void		rotate_plane(t_rot_axis axis);
void		move_sphere(t_move move);
void		move_plane(t_move move);

//keyhook
void		hook(void *param);

//main
void		put(void);
int			setup(mlx_t **mlx);

#endif