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
