/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/23 16:52:36 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	samples(int x, int y)
{
	int		s;
	t_ray	ray;
	double	scale;
	t_color	c[2];
	double	xy[2];

	scale = 1.0 / SAMPLES;
	s = 0;
	c[1] = (t_color){0, 0, 0, 1};
	while (s < SAMPLES)
	{
		xy[0] = (x + random_double()) / (double)(data()->width -1);
		xy[1] = (y + random_double()) / (double)(data()->height - 1);
		ray = get_ray(xy[0], xy[1]);
		c[0] = color_room(ray, (t_vec2){x, y}, 50);
		c[1] = color_add(c[1], c[0]);
		++s;
	}
	c[1] = color_scalar(c[1], scale, 1);
	return (c[1]);
}

t_color	one_sample(int x, int y)
{
	t_ray	ray;
	t_color	c;
	double	xy[2];

	xy[0] = x / (double)(data()->width -1);
	xy[1] = y / (double)(data()->height - 1);
	ray = get_ray(xy[0], xy[1]);
	c = color_room(ray, (t_vec2){x, y}, 50);
	return (c);
}

int	setup(mlx_t **mlx)
{
	mlx_image_t	*g_img;

	*mlx = mlx_init(data()->width, data()->height, "MLX42", true);
	if (!(*mlx))
		return (EXIT_FAILURE);
	g_img = mlx_new_image(*mlx, data()->width, data()->height);
	data()->g_img = g_img;
	data()->b_light = false;
	if (!data()->g_img || (mlx_image_to_window(*mlx, data()->g_img, 0, 0) < 0))
		ft_error();
	return (EXIT_SUCCESS);
}

void	put(void)
{
	int			y;
	int			x;
	uint32_t	rgba;

	y = 0;
	while (y < data()->height)
	{
		x = 0;
		while (x < data()->width)
		{
			if (SAMPLES == 1)
				rgba = get_rgba(one_sample(x, y));
			else
				rgba = get_rgba(samples(x, y));
			mlx_put_pixel(data()->g_img, x, data()->height - 1 - y, rgba);
			x++;
		}
		y++;
	}
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;

	init_ratios();
	if (parser(ac, av[1]) == -1)
		error_handling(2);
	if (SAMPLES < 1)
		error_handling(4);
	if (setup(&mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	put();
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	return (finish_program(mlx));
}
