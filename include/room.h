/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:13 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/09 14:35:18 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include "vector.h"

typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_camera		t_camera;
typedef struct s_room		t_room;
typedef struct s_light		t_light;
typedef struct s_viewport	t_viewport;

struct s_sphere {
	t_vec3	center;
	double	radius;
	t_color	color;
};

struct s_plane {
	t_vec3	p;
	t_vec3	normal;
	t_vec3	c;
	t_color	color;
};

struct s_camera {
	t_vec3	ray_origin;
	t_vec3	ray_direction;
};

struct s_light {
	t_vec3	ray_origin;
	t_vec3	ray_direction;
};

struct s_room {
	t_camera	camera;
	t_light		light;
	t_plane		planes[4];
	t_sphere	spheres[4];
};

struct s_viewport {
	t_vec3		dir;
	double		V_WIDTH;
	double		V_HEIGHT;
};

void	init_spheres(t_sphere spheres[4]);
void	init_plane(t_plane* plane);
void	init_room(t_room *room);
void	init_viewport(t_viewport *viewport, double distance, double v_height, double v_width);


double	hit_sphere(t_sphere sphere, t_vec3 ray_origin, t_vec3 ray_direction);
double	hit_plane(t_plane plane, t_vec3 ray_origin, t_vec3 ray_direction);
t_color		get_color(t_vec3 hitpos, t_vec3 center, t_color colorSphere);

#endif