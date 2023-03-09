/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:15:07 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/09 14:57:26 by tdehne           ###   ########.fr       */
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
# include "utils.h"
# include "../MLX42/include/MLX42/MLX42.h"
# define WIDTH 1200
# define HEIGHT 1000
# define VH 12
# define VW 12

typedef struct s_window	t_window;

void	color_spheres(t_window window, t_sphere spheres[4]);
void	color_plane(t_window window, t_room room, double t_min, double *t_closest, int i);
void	color_room(t_window window, t_room room);
void	color_sphere(t_window window, t_room room, double t_min, double *t_closest, int i);
void	color_planeX(t_window window, t_plane plane);

struct s_window {
	mlx_image_t	*g_img;
	double		x;
	double		y;
	t_vec2		coords;
};

#endif
