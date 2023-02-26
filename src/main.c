/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/02/26 17:52:52 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
// #include "vector.h"
#include "../include/utils.h"
#include "../include/room.h"

static mlx_image_t	*g_img;

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	mlx_t		*mlx;
	t_window	window;
	t_sphere	spheres[4];

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(g_img->pixels, 0, g_img->width * g_img->height * sizeof(int));
	if (!g_img || (mlx_image_to_window(mlx, g_img, 0, 0) < 0))
		ft_error();
	//provisorisches window und spheres initialisieren ... soll noch geändert werden
	window.g_img = g_img;
	window.y = 0.0;
	init_spheres(spheres);

	//raytracing
	while (window.y < HEIGHT)
	{
		window.x = 0.0;
		while (window.x < WIDTH)
		{
			window.coords.x = (window.x * VW / (WIDTH -1) - (VW / 2));
			window.coords.y = (window.y * VH / (HEIGHT - 1) - (VH / 2)) * -1;
			color_spheres(window, spheres);
			++(window.x);
		}
		++(window.y);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
