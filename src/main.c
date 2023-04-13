/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/13 15:56:33 by dns              ###   ########.fr       */
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

typedef struct e_args
{
	int	x;
	int	y;
	int	y_max;
}	t_args;


void	*multi_thread(void *args)
{
	t_args	*pargs;
	int		s;
	t_color	color;
	double samples = 10;
	double	scale = 1.0 / samples;

	pargs = (t_args *)args;
	printf("%i -- %i %i\n", (pargs->y * WIDTH) + pargs->x, pargs->y, pargs->x);
	color = (t_color){0, 0, 0, 1};
	data()->coord.x = pargs->x;
	s = 0;
	while (s < samples)
	{					
		data()->h = ((pargs->x + random_double()) / (double)(WIDTH -1));
		data()->v = ((pargs->y + random_double()) / (double)(HEIGHT - 1));
		data()->ray = get_ray();
		color = color_add(color, color_room(data()->ray, data()->coord, 50));
		++s;
	}
	color.r = sqrt(scale * color.r);
	color.g = sqrt(scale * color.g);
	color.b = sqrt(scale * color.b);

	mlx_put_pixel(data()->g_img, pargs->x, pargs->y_max, get_rgba(color));
	return (NULL);
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;
	pthread_t	*threads;
	t_args		args;
	int	start = clock();
	int	x;
	int	y;
	int	y_max = HEIGHT - 1;

	threads = (pthread_t *)malloc((WIDTH * HEIGHT) * sizeof(pthread_t));
	parser(ac, av[1]);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();
	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		data()->coord.y = y;
		while (x < WIDTH)
		{
			args.x = x;
			args.y = y;
			args.y_max = y_max;
			pthread_create(&threads[(y * WIDTH) + x], NULL, multi_thread, (void *)&args);
			// multi_thread((t_args){x, y, y_max});
			printf("%i\n", x);
			++x;
		}
		++y;
		y_max--;
	}
	x = 0;
	while (x < (WIDTH * HEIGHT))
	{
		pthread_join(threads[x], NULL);
		x++;
	}
	free(threads);
	int end = clock();
	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
