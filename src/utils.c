#include <time.h>
#include <stdlib.h>
#include <miniRT.h>

double	random_double(void)
{
	return ((double)rand() / (RAND_MAX));
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
		// printf("random point x %f %f %f\n", random_point.x, random_point.y, random_point.z);
		init_vec3(&random_point, random_min_max(-1, 1), random_min_max(-1, 1), random_min_max(-1, 1));
		if (vec3_length(random_point) >= 1)
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