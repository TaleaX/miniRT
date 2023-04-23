/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 14:32:39 by dantonik          #+#    #+#             */
/*   Updated: 2023/04/22 23:13:59 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	rotate_plane(t_rot_axis axis)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == PLANE)
		{
			if (axis == X)
				data()->objects[i].normal = vec3_rotate_x(data()->objects[i].normal, 90);
			else if (axis == Y)
				data()->objects[i].normal = vec3_rotate_y(data()->objects[i].normal, 90);
			else if (axis == Z)
				data()->objects[i].normal = vec3_rotate_z(data()->objects[i].normal, 90);
		}
		++i;
	}
}

void	rotate_cylinder(t_rot_axis axis)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == CYLINDER)
		{
			if (axis == X)
				data()->objects[i].axis = vec3_rotate_x(data()->objects[i].axis, 90);
			else if (axis == Y)
				data()->objects[i].axis = vec3_rotate_y(data()->objects[i].axis, 90);
			else if (axis == Z)
				data()->objects[i].axis = vec3_rotate_z(data()->objects[i].axis, 90);

		}
		++i;
	}
}

void	rotate(mlx_t	*mlx, t_rot_axis axis)
{
	if (mlx_is_key_down(mlx, MLX_KEY_P))
	{
		mlx_delete_image(mlx, data()->g_img);
		data()->g_img = mlx_new_image(mlx, data()->width, data()->height);
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		rotate_plane(axis);
		put();
	}
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		mlx_delete_image(mlx, data()->g_img);
		data()->g_img = mlx_new_image(mlx, data()->width, data()->height);
		mlx_image_to_window(mlx, data()->g_img, 0, 0);
		rotate_cylinder(axis);
		put();
	}
}


void	move_cylinder(t_move move)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == CYLINDER)
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
		}
		++i;
	}
}

void	move(mlx_t	*mlx, t_move move)
{
	mlx_delete_image(mlx, data()->g_img);
	data()->g_img = mlx_new_image(mlx, data()->width, data()->height);
	mlx_image_to_window(mlx, data()->g_img, 0, 0);
	move_cylinder(move);
	put();
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

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

int	finish_program(mlx_t *mlx)
{
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void	init_ratios(void)
{
	data()->height = 600;
	data()->aspect_ratio = (double)(3.0 / 2.0);
	data()->width = (int)(data()->height * data()->aspect_ratio);
	data()->vh = 1.0f;
	data()->vw = (double)(data()->vh * data()->aspect_ratio);
}
