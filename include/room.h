#ifndef classes_H
# define classes_H
# include "miniRT.h"
// # include "vector.h"

typedef struct sphere Sphere;
typedef struct camera Camera;

void	initSphere(void* self, Vec3 center, double radius);
void	initCamera(void* self, Vec3 rayOrigin, Vec3 rayDirection);
void	initRoom(void* self);

// void	colorSphere (Vec3 hitPos, Window window);
void	color(void* self, Window window);
void	changeRadius(void* self, double radius);
void	changeCenter(void* self, double x, double y, double z);
// void		moveCamera(void* self);

struct sphere {
	Vec3	center;
	double	radius;
	void	(*changeRadius)(void* self, double radius);
	void	(*color)(void* self, Window window);
	void	(*changeCenter)(void* self, double x, double y, double z);
};

typedef struct plane {
	
} Plane;

typedef struct cylinder {
	
} Cylinder;

struct camera {
	Vec3 rayOrigin;
	Vec3 rayDirection;
};

typedef struct room {
	Sphere		sphere[4];
	Plane		plane[4];
	Cylinder	cylinder[4];
	Camera		camera;
	// void (*init)(void* self);
	// void (*moveCamera)(void* self);
} Room;

#endif