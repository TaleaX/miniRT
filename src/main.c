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
#include "../include/color.h"
#include "../include/calc.h"
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
	t_color		color;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return (EXIT_FAILURE);
	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
		ft_error();

	init_data();
	double	scale = 1.0 / 10.0;
	int	start = clock();
	int s;
	int	x;
	int	y = 0;
	double	test = 0.5;
	double	verschiebung;
	double	base_verschiebung = 0.5;

	data()->ray.origin.y = 5;
	verschiebung = base_verschiebung + data()->ray.origin.y;
	// test = VH * verschiebung;
	
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = (t_color){0, 0, 0, 1};
			s = 0;
			while (s < 10)
			{					
				data()->coord.x = x;
				data()->coord.y = y;
				data()->ray.direction.x = ((x) * VW / (double)(WIDTH -1) - (VW * 0.5)) - data()->ray.origin.x;
				data()->ray.direction.y = (((y) * VH / (double)(HEIGHT- 1) - (VH * verschiebung)) * -1) - data()->ray.origin.y;
				// data()->px[x][y].ray.direction.z = 1;
				color = color_add(color, color_room(data()->ray, data()->coord, 50));
				// color = sampling(window, room);
				++s;
			}
			// printf("y %f\n", data()->ray.direction.y);
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);
			// color.r *= scale;
			// color.g *= scale;
			// color.b *= scale;
			mlx_put_pixel(data()->g_img, x, y, get_rgba(color));
			++x;
		}
		++y;
	};
	int end = clock();
	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
