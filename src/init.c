#include "room.h"

void	initSphere(void* self, Vec3 center, double radius) {
	Sphere*	this;

	this = self;
	this->center = center;
	this->radius = radius;
	this->changeRadius = changeRadius;
	this->color = color;
	this->changeCenter = changeCenter;
	
}
void	initCamera(void* self, Vec3 rayOrigin, Vec3 rayDirection) {
	Camera*	this = self;
	this->rayOrigin = rayOrigin;
	this->rayDirection = rayDirection;
}

void	initVec3(void* self, double x, double y, double z) {
	Vec3* this;

	this = self;
	this->x = x;
	this->y = y;
	this->z = z;
	this->length = length;
	this->normalize = normalize;
	this->hitPos = hitPos;
	this->changeCoords = changeCoords;
}

void	initRoom(void* self) {
	Room*	this;
	Vec3	rayOrigin;
	Vec3	rayDirection;
	Vec3	sphereOrigin;
	int		i;

	i = 0;
	this = self;
	initVec3(&rayOrigin, 0.0, 0.0, 5.0);
	initVec3(&rayDirection, 0.0, 0.0, -1.0);
	initVec3(&sphereOrigin, 0.0, 0.0, 0.0);
	initCamera(&(this->camera), rayOrigin, rayDirection);
	while (i < 4) {
		initSphere(&this->sphere[i], sphereOrigin, 0.5);
		this->sphere[i].changeCenter(&this->sphere[i], 0, i, 0);
		++i;
	}
}


void	initWindow(Window* window, mlx_image_t* img) {
	Vec3 viewport;

	initVec3(&viewport, 0, 0, 1);
	window->img = img;
	window->viewport = viewport;
}