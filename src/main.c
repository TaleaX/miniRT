/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dns <dns@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:17:01 by tdehne            #+#    #+#             */
/*   Updated: 2023/03/30 15:41:47 by dns              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include "../include/color.h"
#include "../include/calc.h"
#include <time.h>
#include <math.h>


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



double	map_y_rotationX(double y_start, double y, double radian)
{
	double	factor;
	factor = sinf(radian);
	// printf("y %f\n", y);
	return ((y * factor + y_start));
}

double	map_z_rotationX(double z_start, double z, double radian)
{
	double	factor;
	factor = cosf(radian);
	return (z_start +  z * factor);
}

double	map_z_rotationY(double z_start, double z, double radian)
{
	double	factor;

	factor = sinf(radian);
	// printf("factor %f %f\n", z * factor, z);
	return (z_start +  z * factor);
}

double	map_x_rotationY(double x_start, double x, double radian)
{
	double	factor;
	factor = cosf(radian);
	// printf("x %f\n", x);
	return ((x * factor + x_start));
}

// int32_t	main(void)
// {
// 	mlx_t		*mlx;
// 	t_color		color;

// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 		return (EXIT_FAILURE);
// 	data()->g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	memset(data()->g_img->pixels, 0, data()->g_img->width * data()->g_img->height * sizeof(int));
// 	if (!data()->g_img || (mlx_image_to_window(mlx, data()->g_img, 0, 0) < 0))
// 		ft_error();

// 	init_data();
// 	// exit(0);
// 	double samples = 5;
// 	double	scale = 1.0 / samples;
// 	int	start = clock();
// 	int s;
// 	int	x;
// 	int	y = 0;
// 	double	test = 0.5;
// 	double	verschiebung_y;
// 	double	base_verschiebung_y = -0.5;
// 	double	base_verschiebung_x = -0.5;
// 	double	verschiebung_x = 0;
// 	double	verschiebung_z;
// 	double	rotation_rad_x = degree_to_radian(90);
// 	double	rotation_rad_y = degree_to_radian(0);
// 	double	y_start;
// 	t_vec3	dist = {0, 0, 1};

// 	// verschiebung_y = base_verschiebung + data()->ray.origin.y;
// 	verschiebung_y = 0;// - 2;

// 	verschiebung_z = 0;
// 	// double	camera_start_y = 5;
// 	// double	camera_start_x = 1;
// 	// double	camera_start_z = -1;



// 	data()->ray.origin.y = verschiebung_y + cosf(rotation_rad_x);
// 	data()->ray.origin.z = verschiebung_z + cosf(rotation_rad_x) * 0.5 - sinf(rotation_rad_x) + sinf(rotation_rad_y) + sinf(rotation_rad_y) * 0.5;
// 	// data()->ray.origin.z = 0;
// 	data()->ray.origin.x = verschiebung_x + sinf(rotation_rad_y);

// 	if (rotation_rad_x >= M_PI && rotation_rad_x <= 2*M_PI)
// 		base_verschiebung_y *= -1;
// 	printf("origin x %f y %f z %f\n", data()->ray.origin.x, data()->ray.origin.y, data()->ray.origin.z);
// 	// printf("%f\n", cosf(rotation_rad_y));
// 	int	y_max = HEIGHT - 1;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		data()->coord.y = y;
// 		double	w_y = (((y ) * VH / (double)(HEIGHT- 1)));
// 		double	w_y_z = (((y) * VH / (double)(HEIGHT- 1)));
// 		data()->viewport_px.y = map_y_rotationX((VH * + base_verschiebung_y + verschiebung_y), w_y, rotation_rad_x);
// 		double y_z = map_z_rotationX(verschiebung_z, w_y_z, rotation_rad_x);
// 		printf("\n---------------map y_z %f----------------\n", y_z);
// 		while (x < WIDTH)
// 		{
// 			color = (t_color){0, 0, 0, 1};
// 			// s = 0;
// 			// while (s < samples)
// 			// {					
// 				data()->coord.x = x;
// 				data()->viewport_px.x = ((x ) * VW / (double)(WIDTH -1));// + (VW * base_verschiebung_x + verschiebung_x);
// 				// data()->viewport_px.y = (((y ) * VH / (double)(HEIGHT- 1)));// + (VH * + base_verschiebung_y + verschiebung_y);
// 				// data()->viewport_px.z = (((y) * VH / (double)(HEIGHT- 1)));
// 				double	w_x_z = (((x ) * VW / (double)(WIDTH- 1)));
// 				// double test_z = (((x) * VW / (double)(WIDTH- 1)));
// 				// printf("%f\n", data()->viewport_px.z);
// 				// data()->viewport_px.z = 1;

// 				data()->viewport_px.x = map_x_rotationY(VW * base_verschiebung_x + verschiebung_x, data()->viewport_px.x, rotation_rad_y);
// 				data()->viewport_px.z = map_z_rotationY(y_z, w_x_z, rotation_rad_y);
// 				double	x_0;
// 				double	x_z_0;
				
// 				if (x == 0) {
// 					x_0 = data()->viewport_px.x;
// 					x_z_0 = data()->viewport_px.z;
// 				}
// 				else if (x == WIDTH - 1) {
// 					printf("from x %f --> %f\t", x_0, data()->viewport_px.x);
// 					printf("from x_z %f --> %f\n", x_z_0, data()->viewport_px.z);
// 				}
// 				data()->ray.direction.x = data()->viewport_px.x -  data()->ray.origin.x;
// 				data()->ray.direction.y = data()->viewport_px.y -  data()->ray.origin.y;
// 				data()->ray.direction.z = data()->viewport_px.z -  data()->ray.origin.z;
// 				// printf("x %f y %f z %f\n", data()->ray.direction.x, data()->ray.direction.y, data()->ray.direction.z);
// 				color = color_add(color, color_room(data()->ray, data()->coord, 50));
// 				// color = sampling(window, room);
// 			// 	++s;
// 			// }
// 			// color.r = sqrt(scale * color.r);
// 			// color.g = sqrt(scale * color.g);
// 			// color.b = sqrt(scale * color.b);

// 			mlx_put_pixel(data()->g_img, x, y_max, get_rgba(color));
// 			// if (y == 0)
// 			// 	printf("x %f y %f z %f\n", data()->viewport_px.x, data()->viewport_px.y, data()->viewport_px.z);
// 			// if (y == HEIGHT - 1)

// 			// printf("x %f y %f z %f\n", data()->viewport_px.x, data()->viewport_px.y, data()->viewport_px.z);
// 			++x;
// 		}
// 		// if (y == HEIGHT - 1) {
// 		// 	printf("y\n");
// 		// 	exit(0);
// 		// }
// 		// printf("%f %f\n",data()->viewport_px.y, data()->viewport_px.z);
// 		// printf("y %f z %f\n", data()->ray.direction.y, data()->ray.direction.z);
// 		// if (y == 3)
// 		// 	exit(0);
// 		++y;
// 		y_max--;
// 	};
// 	int end = clock();
// 	printf("origin x %f y %f z %f\n", data()->ray.origin.x, data()->ray.origin.y, data()->ray.origin.z);

// 	// exit(0);
// 	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
// 	mlx_loop_hook(mlx, &hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }


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

	// double samples = 20;
	// double	scale = 1.0 / samples;
	int	start = clock();
	// int s;
	int	x;
	int	y = 0;
	double	base_verschiebung_y = -0.5;
	double	base_verschiebung_x = -0.5;
	// double	y_start;

	// int	y_max = HEIGHT - 1;
	y = HEIGHT - 1;
	// printf("%f %f\n", data()->ray.origin.z, data()->camera.origin.z);
	// exit(0);
	data()->viewport_px.z = -2;
	while (y >= 0)
	{
		x = 0;
		data()->coord.y = y;
		while (x < WIDTH)
		{
			color = (t_color){0, 0, 0, 1};
			// s = 0;
			// while (s < samples)
			// {					
				data()->viewport_px.y = (((y) * data()->camera.viewport_height / (double)(HEIGHT - 1)) + (data()->camera.viewport_height * base_verschiebung_y)) * -1;
				data()->coord.x = x;
				data()->viewport_px.x = ((x) * data()->camera.viewport_width / (double)(WIDTH -1)) + (data()->camera.viewport_width * base_verschiebung_x);

				data()->ray.direction.x = data()->viewport_px.x -  data()->ray.origin.x;
				data()->ray.direction.y = data()->viewport_px.y -  data()->ray.origin.y;
				data()->ray.direction.z = data()->viewport_px.z -  data()->ray.origin.z;

				color = color_add(color, color_room(data()->ray, data()->coord, 50));
				// color = sampling(window, room);
			// 	++s;
			// }
			// color.r = sqrt(scale * color.r);
			// color.g = sqrt(scale * color.g);
			// color.b = sqrt(scale * color.b);

			mlx_put_pixel(data()->g_img, x, y, get_rgba(color));
			++x;
		}
		--y;
		// y_max--;
	};
	int end = clock();
	printf("%f\n", (float)(end - start) / CLOCKS_PER_SEC);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
