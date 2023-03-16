/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/15 06:31:21 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
// #include "vector.h"
#include "../include/color.h"
#include "../include/calc.h"
#include "../include/room.h"
#include <time.h>

// static mlx_image_t	*g_img;

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

t_color	test(t_vec3 origin, t_vec3 dir, t_sphere spheres[4]);

t_data	*data(void)
{
	static t_data data;
	return (&data);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	t_window	window;
	t_room		room;
	t_color		color;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();

	init_room(&room);
	init_window(&window, data()->g_img, HEIGHT, WIDTH);
	double	scale = 1.0 / 15.0;
	int	start = clock();
	int s;
	while (window.y < WIDTH)
	{
		window.x = 0;
		while (window.x < HEIGHT)
		{
			// color = (t_color){0, 0, 0, 1};
			// s = 0;
			// while (s < 15)
			// {
				// room.camera.ray.direction.x = room.camera.lower_left_corner.x + ((window.x + random_double()) / (double)(WIDTH - 1)) * VW;
				// room.camera.ray.direction.x = ((window.x * random_double()) * VW / (double)(WIDTH -1) - (VW / 2.0)) - room.camera.ray.origin.x;
				// room.camera.ray.direction.y = room.camera.lower_left_corner.y + ((window.y + random_double()) / (double)(HEIGHT - 1)) * VH;
				// room.camera.ray.direction.y = (((window.y * random_double()) * VH / (double)(HEIGHT- 1) - (VH/ 2.0)) * -1) - room.camera.ray.origin.y;
				// color = color_add(color, color_room(room.camera.ray, room, 50));
				color = sampling(window, room);
			// 	++s;
			// }
			// color.r = sqrt(scale * color.r);
			// color.g = sqrt(scale * color.g);
			// color.b = sqrt(scale * color.b);
			// color.r *= scale;
			// color.g *= scale;
			// color.b *= scale;
			mlx_put_pixel(data()->g_img, window.x, window.y, get_rgba(color));
			++(window.x);
		}
		++(window.y);
	};
	int end = clock();
	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
