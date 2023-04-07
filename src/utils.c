#include "miniRT.h"

double	random_double(void)
{
	return ((double)rand() / (double)((double)RAND_MAX + 1.0));
}

double	random_min_max(double min, double max)
{
	return (random_double() * (max - min) + min);
}

t_vec3	random_in_usphere(void)
{
	t_vec3	random_point;

	while (true)
	{
		init_vec3(&random_point, random_min_max(-1, 1), random_min_max(-1, 1), random_min_max(-1, 1));
		if (vec3_length_squared(random_point) >= 1)
			continue;
		return (random_point);
	}
}

t_vec3	random_in_udisk(void)
{
	t_vec3	random_point;

	while (true)
	{
		init_vec3(&random_point, random_min_max(-1, 1), random_min_max(-1, 1), 0);
		if (vec3_length_squared(random_point) >= 1)
			continue;
		return (random_point);
	}
}

t_vec3	random_in_hemisphere(t_vec3 normal)
{
	t_vec3	in_usphere;

	in_usphere = random_in_usphere();
	if (vec3_dot(in_usphere, normal) > 0.0)
		return (in_usphere);
	return (vec3_scalar(in_usphere, -1));
}

t_vec3	reflected_direction(t_vec3 lightRay, t_vec3 normal)
{
	double	scalar;

	scalar = vec3_dot(lightRay, normal) * 2;

	return (vec3_subtraction(vec3_scalar(normal, scalar),lightRay));

}


void set_face_normal(t_ray ray, t_vec3 *outward_normal)
{
	bool front_face = vec3_dot(ray.direction, *outward_normal) < 0;
	*outward_normal = front_face ? *outward_normal : vec3_scalar(*outward_normal, -1);
}

bool	near_zero(t_vec3 vec)
{
	double	n_pos;
	double	n_neg;

	n_pos = 1e-8;
	n_neg = -1e-8;

	return (vec.x < n_pos && vec.x > n_neg && vec.y < n_pos && vec.y > n_neg && vec.z < n_pos && vec.z > n_neg);
}

double	degree_to_radian(double degree)
{
	return (degree * 2 * M_PI / 360.0);
}

t_ray	get_ray()
{
	t_ray	ray;
	t_vec3	x;
	t_vec3	y;
	t_vec3	viewport_px;
	t_vec3	rd;
	t_vec3	offset;

	// rd = vec3_scalar(random_in_udisk(), data()->camera.lens_radius);
	// offset = vec3_add(vec3_scalar(data()->camera.u, rd.x), vec3_scalar(data()->camera.v, rd.y));

	x = vec3_scalar(data()->camera.viewport_horizontal, data()->h);
	y = vec3_scalar(data()->camera.viewport_vertical, data()->v);
	viewport_px = vec3_add(data()->camera.lower_left_corner, vec3_add(x, y));

	ray.origin = data()->camera.origin;//vec3_add(data()->camera.origin, offset);
	ray.direction = vec3_subtraction(ray.origin, viewport_px);//vec3_subtraction(offset, vec3_subtraction(ray.origin, viewport_px));
	return (ray);
}