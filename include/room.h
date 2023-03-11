/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:13 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 16:49:39 by tdehne           ###   ########.fr       */
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
typedef enum e_light_type	t_light_type;

enum e_light_type
{
	POINT,
	SUN,
	AMBIENT
};

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
	t_vec3	origin;
	t_vec3	direction;
};

struct s_light {
	t_light_type	type;
	t_vec3			origin;
	t_vec3			direction;
};

struct s_room {
	t_camera	camera;
	t_light		light;
	t_plane		planes[4];
	t_sphere	spheres[4];
	size_t		num_spheres;
	size_t		num_lights;
	size_t		num_planes;
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


#endif