#include "miniRT.h"

double dot_produkt(Vec3 v1, Vec3 v2) {
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double vec3_length(Vec3  vec) {
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

void	vec3_normalize(Vec3* vec) {
	double length = vec3_length(*vec);
	(*vec).x /= length; 
	(*vec).y /= length; 
	(*vec).z /= length; 
}

Vec3 vec3_subtraction(Vec3  vec1, Vec3 vec2) {
	Vec3 v;

	v.x = vec2.x - vec1.x;
	v.y = vec2.y - vec1.y;
	v.z = vec2.z - vec1.z;

	return (v);
}