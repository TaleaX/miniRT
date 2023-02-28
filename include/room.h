/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:13 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 16:31:30 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include "vector.h"

typedef struct s_sphere	t_sphere;
typedef struct s_plane	t_plane;
typedef struct s_camera	t_camera;

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

void	init_spheres(t_sphere spheres[4]);
void	init_plane(t_plane* plane);

#endif