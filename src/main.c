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
#include <math.h>
# define M_PI 3.14159265358979323846

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

double	degree_to_radian(double degree)
{
	return (degree * 2 * M_PI / 360.0);
}

double	map_y(double y_start, double y, double radian)
{
	double	factor;
	factor = sinf(radian);
	// printf("y %f\n", y);
	return ((y * factor + y_start));
}

double	map_z(double z_start, double z, double radian)
{
	double	factor;
	factor = cosf(radian);
	return (z_start +  z * factor);
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
	double samples = 20;
	double	scale = 1.0 / samples;
	int	start = clock();
	int s;
	int	x;
	int	y = 0;
	double	test = 0.5;
	double	verschiebung_y;
	double	base_verschiebung_y = -0.5;
	double	base_verschiebung_x = -0.5;
	double	verschiebung_x = 0;
	double	verschiebung_z;
	double	rotation_deg = degree_to_radian(90);
	double	y_start;
	t_vec3	dist = {0, 0, 1};

	// verschiebung_y = base_verschiebung + data()->ray.origin.y;
	verschiebung_y = 0;// - 2;

	verschiebung_z = -1;



	data()->ray.origin.y = verschiebung_y + cosf(rotation_deg);
	data()->ray.origin.z = verschiebung_z + cosf(rotation_deg) * 0.5 - sinf(rotation_deg);
	data()->ray.origin.x = verschiebung_x;
	// printf("origin y %f z %f\n", data()->ray.origin.y, data()->ray.origin.z);
	if (rotation_deg >= M_PI && rotation_deg <= 2*M_PI)
		base_verschiebung_y *= -1;

	int	y_max = HEIGHT - 1;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = (t_color){0, 0, 0, 1};
			s = 0;
			while (s < samples)
			{					
			// 	data()->coord.x = x;
				data()->coord.y = y;
				data()->viewport_px.x = ((x) * VW / (double)(WIDTH -1)) + (VW * base_verschiebung_x + verschiebung_x);
				data()->viewport_px.y = (((y) * VH / (double)(HEIGHT- 1)));
				// data()->viewport_px.z = (((y +  random_double()) * VH / (double)(HEIGHT- 1)));
				data()->viewport_px.z = 1;

				data()->viewport_px.y = map_y((VH * + base_verschiebung_y + verschiebung_y), data()->viewport_px.y, rotation_deg);
				data()->viewport_px.z = map_z(verschiebung_z, data()->viewport_px.z, rotation_deg);
				// printf("%f\n", data()->viewport_px.z);
				
				data()->ray.direction.x = data()->viewport_px.x -  data()->ray.origin.x;
				data()->ray.direction.y = data()->viewport_px.y -  data()->ray.origin.y;
				data()->ray.direction.z = data()->viewport_px.z -  data()->ray.origin.z;
				
				color = color_add(color, color_room(data()->ray, data()->coord, 50));
				// color = sampling(window, room);
				++s;
			}
			color.r = sqrt(scale * color.r);
			color.g = sqrt(scale * color.g);
			color.b = sqrt(scale * color.b);

			mlx_put_pixel(data()->g_img, x, y_max, get_rgba(color));
			++x;
		}
		// printf("%f %f\n",data()->viewport_px.y, data()->viewport_px.z);
		// printf("y %f z %f\n", data()->ray.direction.y, data()->ray.direction.z);

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
