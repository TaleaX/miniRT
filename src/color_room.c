#include "miniRT.h"


void	color_room(t_window window, t_room room)
{
	double		t_min;
	double		t_sphere;
	double		t_plane;
	size_t		i;
	double		t_closest;

	i = 0;
	t_closest = __DBL_MAX__;
	init_vec3(&room.camera.ray_direction, window.coords.x, window.coords.y, 1);
	vec3_normalize(&room.camera.ray_direction);
	t_plane = hit_plane(room.planes[0], room.camera.ray_origin, room.camera.ray_direction);
	while (i < 4)
	{
		t_sphere = hit_sphere(room.spheres[i], room.camera.ray_origin, room.camera.ray_direction);
		if (t_sphere < t_plane)
		{
			// printf("t sphere %f < t_plane %f\n", t_sphere, t_plane);
			color_sphere(window, room, t_sphere, &t_closest, i);
		}
		else if (t_plane <= t_sphere)
		{
			printf("t plane %f <= t_sphere %f\n", t_plane, t_sphere);
			color_plane(window, room, t_plane, &t_closest, i);
		}
		++i;
	}
	// if (t_closest == __DBL_MAX__)
	// 	mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);
}