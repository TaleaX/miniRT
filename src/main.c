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

static mlx_image_t	*g_img;

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

int32_t	main(void)
{
	mlx_t		*mlx;
	t_window	window;
	t_viewport	viewport;
	t_room		room;
	t_color		color;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(g_img->pixels, 0, g_img->width * g_img->height * sizeof(int));
	if (!g_img || (mlx_image_to_window(mlx, g_img, 0, 0) < 0))
		ft_error();

	init_room(&room);
	init_window(&window, g_img, HEIGHT, WIDTH);
	init_viewport(&viewport, 1, VH, VW);

	while (window.y < WIDTH)
	{
		window.x = 0.0;
		while (window.x < HEIGHT)
		{
			viewport.dir.x = (window.x * viewport.V_WIDTH / (double)(window.WIN_WIDTH -1) - (viewport.V_WIDTH / 2.0));
			viewport.dir.y = (window.y * viewport.V_HEIGHT / (double)(window.WIN_HEIGHT- 1) - (viewport.V_HEIGHT / 2.0)) * -1;
			room.camera.direction = viewport.dir;

			color = color_room(room.camera.origin, room.camera.direction, room);
			mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_rgba(color));
			++(window.x);
		}
		++(window.y);
	}
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
