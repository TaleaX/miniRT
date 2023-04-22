/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 15:13:12 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	samples(int x, int y)
{
	int		s;
	t_ray	ray;
	double	scale;
	t_color	c[2];
	double	xy[2];

	scale = 1.0 / SAMPLES;
	s = 0;
	while (s < SAMPLES)
	{
		xy[0] = (x + random_double()) / (double)(WIDTH -1);
		xy[1] = (y + random_double()) / (double)(HEIGHT - 1);
		ray = get_ray(xy[0], xy[1]);
		c[0] = color_room(ray, (t_vec2){x, y}, 50);
		c[1] = color_add(data()->px[y][x].c, c[0]);
		data()->px[y][x].c = c[1];
		++s;
	}
	data()->px[y][x].c.r *= scale;
	data()->px[y][x].c.g *= scale;
	data()->px[y][x].c.b *= scale;
	++x;
}

void	one_sample(int x, int y)
{
	t_ray	ray;
	t_color	c[2];

	ray = get_ray(x / (double)(WIDTH -1), y / (double)(HEIGHT - 1));
	c[0] = color_room(ray, (t_vec2){x, y}, 50);
	c[1] = color_add(data()->px[y][x].c, c[0]);
	data()->px[y][x].c = c[1];
}

void	calc(void)
{
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (SAMPLES <= 1)
				one_sample(x, y);
			else
				samples(x, y);
			++x;
		}
		++y;
	}
}

int	setup(mlx_t **mlx)
{
	int			i;
	int			j;
	t_color		color;
	mlx_image_t	*g_img;

	*mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!(*mlx))
		return (EXIT_FAILURE);
	g_img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	data()->g_img = g_img;
	if (!data()->g_img || (mlx_image_to_window(*mlx, data()->g_img, 0, 0) < 0))
		ft_error();
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			color = (t_color){0, 0, 0, 1};
			data()->px[i][j].color = color;
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	int			i;
	int			j;
	uint32_t	rgba;

	parser(ac, av[1]);
	if (setup(&mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	calc();
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			rgba = get_rgba(data()->px[i][j].c);
			mlx_put_pixel(data()->g_img, j, HEIGHT - 1 - i, rgba);
			j++;
		}
		i++;
	}
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	return (finish_program(mlx));
}
