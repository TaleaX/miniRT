#ifndef VECTORMATH_H
# define VECTORMATH_H
# include <math.h>

typedef struct v2 Vec2;
typedef struct v3 Vec3;
typedef struct v4 Vec4;

void	initVec3(void* self, double x, double y, double z);

double	length(void* self);
void	normalize(void* self);
void	hitPos(void* self, Vec3 rayorigin, Vec3 rayDirection, double t);

struct v2 {
	double	x;
	double	y;
};

struct v3 {
	double 	x;
	double	y;
	double	z;
	double	(*length)(void* self);
	void	(*normalize)(void* self);
	void	(*hitPos)(void* self, Vec3 rayorigin, Vec3 rayDirection, double t);
};

struct v4 {
	double r;
	double g;
	double b;
	double a;
};


double	dot_produkt(Vec3 v1, Vec3 v2);
Vec3	vec3_subtraction(Vec3  vec1, Vec3 vec2);

#endif