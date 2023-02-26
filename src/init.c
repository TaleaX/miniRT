/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:16:51 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 17:22:26 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"

void	init_vec3(void *self, double x, double y, double z)
{
	t_vec3	*this;

	this = self;
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = length;
	this->normalize = normalize;
	this->change_coords = change_coords;
}
