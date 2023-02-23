#ifndef classes_H
# define classes_H
# include "miniRT.h"
# include "vectorMath.h"

void	initSphere(void* self, Vec3 center, double radius);
void	initCamera(void* self, Vec3 rayOrigin, Vec3 rayDirection);
void	changeRadius(void* self, double radius);
void	changeCenter(void* self, Vec3 center);

typedef struct sphere {
	Vec3	center;
	double	radius;
	void	(*changeRadius)(void* self, double radius);
	void	(*changeCenter)(void* self, Vec3 center);
} Sphere;

typedef struct plane {
	
} Plane;

typedef struct cylinder {
	
} Cylinder;

typedef struct camera {
	Vec3 rayOrigin;
	Vec3 rayDirection;
} Camera;

typedef struct room {
	Sphere		sphere[4];
	Plane		plane[4];
	Cylinder	cylinder[4];
	Camera		camera;
	// void (*init)(void* self);
	void (*moveCamera)(void* self);
} Room;

#endif