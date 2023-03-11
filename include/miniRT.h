/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 16:07:54 by tdehne           ###   ########.fr       */
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
# define WIDTH 800
# define HEIGHT 800
# define VH 1
# define VW 1

typedef struct s_window		t_window;
typedef struct s_viewport	t_viewport;


// void	color_spheres(t_window window, t_sphere spheres[4]);
// void	color_plane(t_window window, t_room room, double t_min, double *t_closest, int i);

// void	color_sphere(t_window window, t_room room, double t_min, double *t_closest, int i);
// void	color_planeX(t_window window, t_plane plane);

struct s_window {
	mlx_image_t	*g_img;
	double		x;
	double		y;
	double		WIN_WIDTH;
	double		WIN_HEIGHT;
};


void	init_window(t_window *window, mlx_image_t *g_img, double height, double width);



#endif
