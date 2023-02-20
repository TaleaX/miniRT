#ifndef VECTORMATH_H
# define VECTORMATH_H
# include "miniRT.h"

double	dot_produkt(Vec3 v1, Vec3 v2);
double	vec3_length(Vec3  vec);
void	vec3_normalize(Vec3* vec);
Vec3	vec3_subtraction(Vec3  vec1, Vec3 vec2);

#endif