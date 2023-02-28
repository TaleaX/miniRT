#include "miniRT.h"

static double	hit_plane(t_plane plane, t_vec3 ray_origin, t_vec3 ray_direction){
	t_vec3	oc;
	double	denominator;
	double	numerator;

	oc = vec3_subtraction(ray_origin, plane.c);
	numerator = vec3_dot(plane.normal, oc);
	denominator = vec3_dot(ray_direction, plane.normal);
	printf("%f %f\n", numerator, denominator);
	if (denominator == 0.0)
		return (-1);
	return (numerator / denominator);
}

// uint32_t get_color(t_vec3 hitpos, t_vec3 center)
// {
// 	t_vec3	normal;
// 	t_color color;

// 	normal = vec3_subtraction(center, hitpos);
// 	vec3_normalize(&normal);
// 	color.r = normal.x * 0.5 + 0.5;
// 	color.g = normal.y * 0.5 + 0.5;
// 	color.b = normal.z * 0.5 + 0.5;
// 	color.a = 1;
// 	return (get_rgba(color));
// }

// void	color_plane(t_window window, t_plane)
// {
// 	double		t_min;
// 	t_vec3		ray_origin;
// 	t_vec3		ray_direction;
// 	t_vec3		hitpos;
// 	size_t		i;
// 	double		t_closest;

// 	i = 0;
// 	t_closest = __DBL_MAX__;
// 	init_vec3(&ray_origin, 0.0, 0.0, -3.0);
// 	init_vec3(&ray_direction, window.coords.x, window.coords.y, 1);
// 	vec3_normalize(&ray_direction);
// 	while (i < 4)
// 	{
// 		t_min = hit_sphere(spheres[i], ray_origin, ray_direction);
// 		if (t_min >= 1 && t_min < t_closest)
// 		{
// 			hitpos = get_hitpos(ray_origin, ray_direction, t_min);
// 			mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_color(hitpos, spheres[i].center)); //get_rgba(sphere[i].color));//
// 			t_closest = t_min;
// 		}
// 		++i;
// 	}
// 	if (t_closest == __DBL_MAX__)
// 		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);
// }

void	color_plane(t_window window, t_plane plane)
{
	t_vec3		ray_origin;
	t_vec3		ray_direction;
	// t_vec3		hitpos;
	double		t;

	init_vec3(&ray_origin, 0.0, 0.0, -6.0);
	init_vec3(&ray_direction, window.coords.x, window.coords.y, 1);
	vec3_normalize(&ray_direction);
	
	t = hit_plane(plane, ray_origin, ray_direction);
	if (t >= 0)
	{
		// hitpos = get_hitpos(ray_origin, ray_direction, t);
		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, get_rgba(plane.color));
	}
	else
		mlx_put_pixel(window.g_img, (int)window.x, (int)window.y, 0x000000ff);

}