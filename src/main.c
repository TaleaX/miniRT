/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/11 16:59:07 by tdehne           ###   ########.fr       */
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
	t_viewport	viewport;
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
	init_viewport(&viewport, 1, VH, VW);
	double	scale = 1.0 / 20.0;
	while (window.y < WIDTH)
	{
		window.x = 0.0;
		while (window.x < HEIGHT)
		{
			color = (t_color){0, 0, 0, 1};
			for (int s = 0; s < 20; ++s) {

				viewport.dir.x = ((window.x + random_double()) * viewport.V_WIDTH / (double)(window.WIN_WIDTH -1) - (viewport.V_WIDTH / 2.0));
				viewport.dir.y = ((window.y + random_double()) * viewport.V_HEIGHT / (double)(window.WIN_HEIGHT- 1) - (viewport.V_HEIGHT / 2.0)) * -1;
				room.camera.direction.x = viewport.dir.x - room.camera.origin.x;//vec3_subtraction(room.camera.origin, viewport.dir);
				room.camera.direction.y = viewport.dir.y - room.camera.origin.y;
				room.camera.direction.z = 1;
				color = color_add(color, color_room(room.camera.origin, room.camera.direction, room));
				// color = color_room(room.camera.origin, room.camera.direction, room);
			}
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);
			mlx_put_pixel(data()->g_img, (int)window.x, (int)window.y, get_rgba(color));
			++(window.x);
		}
		++(window.y);
	};
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
