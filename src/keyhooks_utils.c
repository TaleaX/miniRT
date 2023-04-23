/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:04:53 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 20:27:12 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_plane(t_rot_axis axis)
{
	size_t	i;
	t_vec3	rotated;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == PLANE)
		{
			if (axis == X)
				rotated = vec3_rotate_x(data()->objects[i].normal, 90);
			else if (axis == Y)
				rotated = vec3_rotate_y(data()->objects[i].normal, 90);
			else
				rotated = vec3_rotate_z(data()->objects[i].normal, 90);
			data()->objects[i].normal = rotated;
		}
		++i;
	}
}

void	rotate_cylinder(t_rot_axis axis)
{
	size_t	i;
	t_vec3	rotated;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == CYLINDER)
		{
			if (axis == X)
				rotated = vec3_rotate_x(data()->objects[i].axis, 90);
			else if (axis == Y)
				rotated = vec3_rotate_y(data()->objects[i].axis, 90);
			else
				rotated = vec3_rotate_z(data()->objects[i].axis, 90);
			data()->objects[i].axis = rotated;
		}
		++i;
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

void	move_sphere(t_move move)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == SPHERE)
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

void	move_plane(t_move move)
{
	size_t	i;

	i = 0;
	while (i < data()->n_objs)
	{
		if (data()->objects[i].obj_type == PLANE)
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
