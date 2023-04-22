/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/22 14:21:38 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
	}
}

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

typedef struct e_args
{
	int	x;
	int	y;
	int	y_max;
}	t_args;

void	one_threaded(void)
{
	double	scale = 1.0 / SAMPLES;
	t_ray	ray;
	int s;
	int	x;
	int	y;
	double h;
	double v;
	int	y_max;
	t_color color;

	color = (t_color){0, 0, 0, 1};
	y_max = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH)
		{
			data()->coord.x = x;
			data()->coord.y = y;
			s = 0;
			while (s < SAMPLES)
			{
				ray = get_ray((x + random_double()) / (double)(WIDTH -1), (y + random_double()) / (double)(HEIGHT - 1));
				data()->px[y][x].c = color_add(data()->px[y][x].c, color_room(ray, (t_vec2){x, y}, 50));
				++s;
			}
			data()->px[y][x].c.r *= scale;
			data()->px[y][x].c.g *= scale;
			data()->px[y][x].c.b *= scale;
			++x;
		}
		++y;
		y_max--;
	};
}

int	setup(mlx_t **mlx)
{
	int		i;
	int		j;
	t_color	color;

	if (!(*mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
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

int	finish_program(mlx_t		*mlx)
{
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;
	int			i;
	int			j;

	parser(ac, av[1]);
	if (setup(&mlx) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	one_threaded();
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			mlx_put_pixel(data()->g_img, j, HEIGHT - 1 - i, get_rgba(data()->px[i][j].c));
			j++;
		}
		i++;
	}
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	return(finish_program(mlx));
}