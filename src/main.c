/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/11 15:42:38 by dns              ###   ########.fr       */
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

void	multi_thread(int x, int y, int y_max)
{
	int		s;
	t_color	color;
	double samples = 1;
	double	scale = 1.0 / samples;

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
}

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
	int	start = clock();
	int	x;
	int	y;
	int	y_max = HEIGHT - 1;
	y = 0;
	// init_data();
	printf("sphere center %f %f %f radius %f\n",data()->objects[0].center.x, data()->objects[0].center.y, data()->objects[0].center.z, data()->objects[0].radius);
	printf("camera origin %f %f %f hvov %f\n",data()->camera.origin.x, data()->camera.origin.y, data()->camera.origin.z, data()->camera.hfov);
	printf("camera lookat %f %f %f\n",data()->camera.lookat.x, data()->camera.lookat.y, data()->camera.lookat.z);

	while (y < HEIGHT - 1)
	{
		x = 0;
		data()->coord.y = y;
		while (x < WIDTH)
		{
			multi_thread(x, y, y_max);
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
