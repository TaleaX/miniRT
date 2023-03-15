/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 04:09:15 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# include "vector.h"
# include "room.h"
# include "color.h"
# include "calc.h"
# include "../MLX42/include/MLX42/MLX42.h"
# define RATIO 1.5f
# define HEIGHT 800
# define VH 1.0f
# define DIST 1.0f

# define WIDTH 800
//(int) (HEIGHT * RATIO)
# define VW 1.0f
//(double)(VH * RATIO)

typedef struct s_window		t_window;
typedef struct s_viewport	t_viewport;
typedef struct s_hit_rec	t_hit_rec;

// void	color_spheres(t_window window, t_sphere spheres[4]);
// void	color_plane(t_window window, t_room room, double t_min, double *t_closest, int i);

// void	color_sphere(t_window window, t_room room, double t_min, double *t_closest, int i);
// void	color_planeX(t_window window, t_plane plane);

typedef struct s_data
{
	mlx_image_t	*g_img;
}	t_data;

t_data	*data(void);

struct s_window {
	mlx_image_t	*g_img;
	int			x;
	int			y;
	int			WIN_WIDTH;
	int			WIN_HEIGHT;
};

struct	s_hit_rec
{
	t_vec3	hitpos;
	t_vec3	normal;
	double	t;
};

void	init_window(t_window *window, mlx_image_t *g_img, double height, double width);
void	init_hit_rec(t_hit_rec *hit_rec, t_vec3 hitpos, t_vec3 normal, double t);
bool	hit_obj(t_hit_rec *rec, t_ray ray, t_room room);

#endif
