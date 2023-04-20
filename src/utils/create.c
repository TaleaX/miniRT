/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 04:29:20 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/20 18:03:30 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	init_ray(&ray, origin, direction);
	return (ray);
}
