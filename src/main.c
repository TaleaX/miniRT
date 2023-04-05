/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/05 12:15:32 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void hook(void *param) {
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE)) {
		mlx_close_window(mlx);
	}

}

t_data	*data(void)
{
	static t_data data;
	return (&data);
}


// double	map_y_rotationX(double y_start, double y, double radian)
// {
// 	double	factor;
// 	factor = sinf(radian);
// 	// printf("y %f\n", y);
// 	return ((y * factor + y_start));
// }

// double	map_z_rotationX(double z_start, double z, double radian)
// {
// 	double	factor;
// 	factor = cosf(radian);
// 	return (z_start +  z * factor);
// }

// double	map_z_rotationY(double z_start, double z, double radian)
// {
// 	double	factor;

// 	factor = sinf(radian);
// 	// printf("factor %f %f\n", z * factor, z);
// 	return (z_start +  z * factor);
// }

// double	map_x_rotationY(double x_start, double x, double radian)
// {
// 	double	factor;
// 	factor = cosf(radian);
// 	// printf("x %f\n", x);
// 	return ((x * factor + x_start));
// }


int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;

	parser(ac, av[1]);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();

	// init_data();

	double samples = 10;
	double	scale = 1.0 / samples;
	int	start = clock();
	int s;
	int	x;
	int	y;
	// double	base_verschiebung_y = -0.5;
	// double	base_verschiebung_x = -0.5;

	int	y_max = HEIGHT - 1;
	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		data()->coord.y = y;
		while (x < WIDTH)
		{
			color = (t_color){0, 0, 0, 1};
			data()->coord.x = x;
			s = 0;
			while (s < samples)
			{					


				data()->h = ((x + random_double()) / (double)(WIDTH -1));
				data()->v = ((y + random_double()) / (double)(HEIGHT - 1));
				data()->ray = get_ray();
				color = color_add(color, color_room(data()->ray, data()->coord, 50));
				++s;
			}
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);

			mlx_put_pixel(data()->g_img, x, y_max, get_rgba(color));
			++x;
		}
		++y;
		y_max--;
	};
	int end = clock();
	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
