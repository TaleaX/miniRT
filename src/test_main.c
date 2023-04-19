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

void	print_render(void)
{
	int	i;
	int	j;
	int	x;
	int	y;
	double	scale = 1.0 / (THREADS * 4);

	if (THREADS > 1)
	{
		y = 0;
		while (y < HEIGHT)
		{
			x = 0;
			while (x < WIDTH)
			{
				data()->px[y][x].c.r = sqrt(scale * data()->px[y][x].c.r);
				data()->px[y][x].c.g = sqrt(scale * data()->px[y][x].c.g);
				data()->px[y][x].c.b = sqrt(scale * data()->px[y][x].c.b);
				mlx_put_pixel(data()->g_img, x, HEIGHT - 1 - y, get_rgba(data()->px[y][x].c));
				x++;
			}
			y++;
		}
	}
	else
	{
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
	}
}

void	one_threaded(void)
{
	double	scale = 1.0 / SAMPLES;
	t_ray	ray;
	int s;
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH - 1)
		{
			ray = get_ray(x / (double)(WIDTH -1), y / (double)(HEIGHT - 1));
			data()->px[y][x].c = color_room(ray, (t_vec2){x, y}, 5);
			++x;
		}
		++y;
	}
	// y = 0;
	// while (y < HEIGHT - 1)
	// {
	// 	x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		if (y >= 0 && x >= 0 && y+5 < HEIGHT - 5 && x+5 < WIDTH - 5 && data()->px[y][x].obj_id != data()->px[y+5][x+5].obj_id)
	// 			data()->px[y][x].c = (t_color){0, 0, 0, 1};
	// 		if (y <= HEIGHT && x <= WIDTH && y-5 > HEIGHT && x-5 > WIDTH && data()->px[y][x].obj_id != data()->px[y-5][x-5].obj_id)
	// 			data()->px[y][x].c = (t_color){0, 0, 0, 1};
	// 		++x;
	// 	}
	// 	++y;
	// }
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	t_color		color;
	int			i;
	int			j;

	data()->start_clock = clock();
	parser(ac, av[1]);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
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
	pre_hit_loop();
	one_threaded();
	print_render();
	ZEIT("End main function:")
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}