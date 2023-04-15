/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/04/14 18:04:17 by dns              ###   ########.fr       */
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
	int		s;
	double	scale = 1.0 / SAMPLES;
	t_ray	ray;

	int	x;
	int	y;
	int	y_max = HEIGHT - 1;
	y = 0;

	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH)
		{
			s = 0;
			while (s < SAMPLES)
			{
				ray = get_ray((x + random_double()) / (double)(WIDTH -1), (y + random_double()) / (double)(HEIGHT - 1));
				pthread_mutex_lock(&data()->px[y][x].m_color);
				data()->px[y][x].c = color_add(data()->px[y][x].c, color_room(ray, (t_vec2){x, y}, 50));
				pthread_mutex_unlock(&data()->px[y][x].m_color);
				++s;
			}
			data()->px[y][x].c.r = sqrt(scale * data()->px[y][x].c.r);
			data()->px[y][x].c.g = sqrt(scale * data()->px[y][x].c.g);
			data()->px[y][x].c.b = sqrt(scale * data()->px[y][x].c.b);
			++x;
		}
		++y;
		y_max--;
	}
	ZEIT("Ende Thread")
	return (NULL);
}

void	multi_threaded(void)
{
	pthread_t	*threads;
	int			i;
	int			j;

	threads = (pthread_t *)malloc(THREADS * sizeof(pthread_t));
	// if (pthread_mutex_init(&data()->put_pixel, NULL) != 0)
	// 	printf("mutex init error!\n");
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (pthread_mutex_init(&data()->px[i][j].m_color, NULL) != 0)
				printf("mutex init error!\n");
			j++;
		}
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_create(&threads[i], NULL, multi_thread, NULL);
		i++;
	}
	ZEIT("Multi Threaded after init/create:")
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		// pthread_detach(threads[i]);
		i++;
	}
	ZEIT("Multi Threaded after join:")
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			pthread_mutex_destroy(&data()->px[i][j].m_color);
			j++;
		}
		i++;
	}
	free(threads);
}

void	one_threaded(void)
{
	double	scale = 1.0 / SAMPLES;
	t_ray	ray;
	int s;
	int	x;
	int	y;
	double h;
	double v;
	t_color color = (t_color){0, 0, 0, 1};

	int	y_max = HEIGHT - 1;
	y = 0;
	// init_data();
	printf("sphere center %f %f %f radius %f\n",data()->objects[0].center.x, data()->objects[0].center.y, data()->objects[0].center.z, data()->objects[0].radius);
	printf("camera origin %f %f %f hvov %f\n",data()->camera.origin.x, data()->camera.origin.y, data()->camera.origin.z, data()->camera.hfov);
	printf("camera lookat %f %f %f\n",data()->camera.lookat.x, data()->camera.lookat.y, data()->camera.lookat.z);

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
			data()->px[y][x].c.r = sqrt(scale * data()->px[y][x].c.r);
			data()->px[y][x].c.g = sqrt(scale * data()->px[y][x].c.g);
			data()->px[y][x].c.b = sqrt(scale * data()->px[y][x].c.b);
			++x;
		}
		++y;
		y_max--;
	};
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;
	int			i;
	int			j;

	printf("Threads: %i Samples: %i Total Samples: %i\n", THREADS, SAMPLES, THREADS * SAMPLES);
	printf("PIXEL: %i\n\n", WIDTH * HEIGHT);
	data()->start_clock = clock();
	parser(ac, av[1]);
	ZEIT("Main function after parser:")
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ZEIT("MLX inited:")
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			data()->px[i][j].color = (t_color){0, 0, 0, 1};
			j++;
		}
		i++;
	}
	ZEIT("Color inited:")
	if (THREADS > 1)
		multi_threaded();
	else
		one_threaded();
	i = 0;
	ZEIT("Main function after threaded:")
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
	ZEIT("End main function:")
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}