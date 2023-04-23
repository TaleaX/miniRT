/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:13 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 20:40:18 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "miniRT.h"
# define SAMPLES 1
# define VIEWPORT_DIST 1.0

//enums
typedef enum e_light_type		t_light_type;
typedef enum e_material_type	t_material_type;
typedef enum e_obj_type			t_obj_type;
typedef enum e_rot_axis			t_rot_axis;
typedef enum e_move				t_move;

//room structs
// typedef struct s_window			t_window;
typedef struct s_pixel			t_pixel;
typedef struct s_data			t_data;
typedef struct s_viewport		t_viewport;
typedef struct s_sphere			t_sphere;
typedef struct s_plane			t_plane;
typedef struct s_camera			t_camera;
typedef struct s_room			t_room;
typedef struct s_light			t_light;
typedef struct s_ray			t_ray;
typedef struct s_obj			t_obj;

//vector structs
typedef struct s_v2				t_vec2;
typedef struct s_v3				t_vec3;
typedef struct s_color			t_color;
// typedef		   t_vec3			t_v3;

enum e_rot_axis {
	X,
	Y,
	Z
};

enum e_move {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FORWARDS,
	BACKWARDS
};

enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
};

enum e_light_type
{
	POINT,
	SUN,
	AMBIENT
};

enum e_material_type
{
	MATTE,
	MIRROR,
	GLAS
};

struct s_v2 {
	int		x;
	int		y;
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

struct s_ray {
	t_vec3	origin;
	t_vec3	direction;
};

struct s_light {
	t_light_type	type;
	t_ray			ray;
	double			intensity;
	t_color			color;
};

struct	s_obj
{
	t_vec3			center;
	t_vec3			point;
	t_vec3			point2;
	t_vec3			normal;
	t_vec3			axis;
	double			radius;
	double			height;
	t_obj_type		obj_type;
	t_color			color;
	t_material_type	material;
	double			fuzz;
	double			specular;
};

t_data	*data(void);

struct s_pixel
{
	int				hits_num;
	t_color			color;
	t_vec3			reverse_ray;
	t_color			c;
	double			t;
	t_vec3			hitpoint;
	int				obj_id;
	t_vec3			normal;
	t_obj_type		type;
	t_material_type	material;
	double			fuzz;
	double			specular;
	double			v;
	double			h;
	t_ray			ray;
	pthread_mutex_t	m_color;
};

struct s_camera {
	t_vec3		origin;
	t_vec3		orientation;
	t_vec3		viewport_vertical;
	t_vec3		viewport_horizontal;
	double		vfov;
	double		hfov;
	t_vec3		lower_left_corner;
	double		lens_radius;
	double		aperture;
	t_vec3		w;
	t_vec3		v;
	t_vec3		u;
};

struct s_data
{
	mlx_image_t	*g_img;
	t_pixel		px[2880][5120];
	t_vec2		coord;
	t_camera	camera;
	t_obj		objects[1000];
	size_t		n_objs;
	size_t		n_lights;
	t_ray		ray;
	t_light		lights[10];
	t_vec3		viewport_px;
	double		v;
	double		h;
	int			samples;
	int			obj_len;
	int			lights_len;
	double		scale;
	double		parse_float[3];
	int			width;
	int			height;
	double		aspect_ratio;
	double		vh;
	double		vw;
	bool		b_light;
};

struct	s_hit_rec
{
	t_vec3			hitpos;
	t_vec3			normal;
	t_material_type	material;
	t_color			color;
	double			radius;
	t_vec3			center;
	double			t;
};

#endif