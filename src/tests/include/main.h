#ifndef TEST_H
# define TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <pthread.h>
# include "../../../MLX42/include/MLX42/MLX42.h"

# define RATIO 1.5f
# define ASPECT_RATIO (double)(3.0 / 2.0)
# define HEIGHT 500
# define THREADS 1
# define SAMPLES 1
# define MAX_T 1000
# define WIDTH ((int)(HEIGHT * ASPECT_RATIO))
# define VH 1.0
# define VW ((double)(VH * ASPECT_RATIO))
# define VIEWPORT_DIST 1.0

typedef enum e_light_type		t_light_type;
typedef enum e_material_type	t_material_type;
typedef enum e_obj_type			t_obj_type;
typedef struct s_hit_rec		t_hit_rec;

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

enum e_obj_type {
	SPHERE,
	PLANE,
	CYLINDER
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
	// t_material_type	material;
	// double			fuzz;
	// double			specular;
};

struct s_pixel
{
	int				hits_num;
	t_color			color;
	t_color			c;
	double			t;
	t_vec3			hitpoint;
	int				obj_id;
	t_vec3			normal;
	t_obj_type		type;
	// t_material_type	material;
	double			fuzz;
	double			specular;
	double			v;
	double			h;
	t_ray			ray;
};

struct s_camera {
	t_vec3		origin;
	t_vec3		lookat;
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
	t_pixel		px[HEIGHT][WIDTH];
	t_vec2		coord;
	t_camera	camera;
	t_obj		objects[1000];
	size_t		n_objs;
	size_t		n_lights;
	t_ray		ray;
	// t_light		lights[10];
	t_vec3		viewport_px;
	double		v;
	double		h;
	int			samples;
	int			obj_len;
	int			lights_len;
	double		scale;
	float		parse_float[3];
};

t_data	*data(void);

t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3	vec3_scalar(t_vec3 vec, double scalar);
double	vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_mult(t_vec3 vec1, t_vec3 vec2);
t_color	color_add(t_color color1, t_color color2);
double	vec3_length_squared(t_vec3 v);

#endif