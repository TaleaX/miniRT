#include "../include/main.h"

t_vec3	vec3_subtraction(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec2.x - vec1.x, vec2.y - vec1.y, vec2.z - vec1.z});
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec3	vec3_scalar(t_vec3 vec, double scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_mult(t_vec3 vec1, t_vec3 vec2)
{
	return ((t_vec3){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

t_color	color_add(t_color color1, t_color color2)
{
	return ((t_color){color1.r + color2.r, color1.g \
	+ color2.g, color1.b + color2.b, color2.a});
}

double	vec3_length_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}