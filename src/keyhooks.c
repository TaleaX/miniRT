/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:05:05 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 20:26:43 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rotate(mlx_t	*mlx, t_rot_axis axis)
{
	mlx_image_t	*g_img;

	if (mlx_is_key_down(mlx, MLX_KEY_P))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		rotate_plane(axis);
		put();
	}
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		rotate_cylinder(axis);
		put();
	}
}

static void	move_all(t_move move)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (move == FORWARDS)
			data()->objects[i].center.z += 1;
		else if (move == BACKWARDS)
			data()->objects[i].center.z -= 1;
		else if (move == LEFT)
			data()->objects[i].center.x -= 1;
		else if (move == RIGHT)
			data()->objects[i].center.x += 1;
		else if (move == UP)
			data()->objects[i].center.y += 1;
		else if (move == DOWN)
			data()->objects[i].center.y -= 1;
		++i;
	}
}

static void	move2(mlx_t *mlx, t_move move)
{
	mlx_image_t	*g_img;

	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		move_sphere(move);
		put();
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		move_all(move);
		put();
	}
}

static void	move(mlx_t	*mlx, t_move move)
{
	mlx_image_t	*g_img;

	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		move_cylinder(move);
		put();
	}
	if (mlx_is_key_down(mlx, MLX_KEY_P))
	{
		mlx_delete_image(mlx, data()->g_img);
		g_img = mlx_new_image(mlx, data()->width, data()->height);
		data()->g_img = g_img;
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		move_plane(move);
		put();
	}
	move2(mlx, move);
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_X))
		rotate(mlx, X);
	if (mlx_is_key_down(mlx, MLX_KEY_Y))
		rotate(mlx, Y);
	if (mlx_is_key_down(mlx, MLX_KEY_Z))
		rotate(mlx, Z);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		move(mlx, FORWARDS);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move(mlx, BACKWARDS);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		move(mlx, RIGHT);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		move(mlx, LEFT);
	if (mlx_is_key_down(mlx, MLX_KEY_U))
		move(mlx, UP);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(mlx, DOWN);
}
