#include "room.h"

void	initSphere(void* self, Vec3 center, double radius) {
	Sphere*	this;

	this = self;
	this->center = center;
	this->radius = radius;
	this->changeRadius = changeRadius;
	this->colorSphere = colorSphere;
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
	Vec3	planeOrigin;
	Vec3	planePoint;
	Vec3	planeNormal;
	int		i;

	i = 0;
	this = self;
	initVec3(&rayOrigin, 0.0, 0.0, 1.0);
	initVec3(&rayDirection, 0.0, 0.0, 1.0);
	initVec3(&sphereOrigin, 0.0, 0.0, 0.0);
	initVec3(&planeOrigin, 0.0, 0.0, 3);
	initVec3(&planeNormal, 0.0, 0.0, 0.1);
	initVec3(&planePoint, 0.0, 0.0, 0.0);
	initCamera(&(this->camera), rayOrigin, rayDirection);
	initPlane(&this->plane[0], planePoint, planeOrigin, planeNormal);
	while (i < 4) {
		initSphere(&this->sphere[i], sphereOrigin, 1);
		this->sphere[i].changeCenter(&this->sphere[i], i, 0, 0);
		// sphereOrigin.changeCoords(&sphereOrigin, i / 2, 0, 0);
		++i;
	}
}

void initPlane(void* self, Vec3 point, Vec3 origin, Vec3 normal) {
	Plane*	this;

	this = self;
	this->point = point;
	this->normal = normal;
	this->origin = origin;
}

void	initWindow(Window* window, mlx_image_t* img) {
	Vec3 viewport;
	Camera	camera;

	initVec3(&viewport, 0, 0, -1);
	window->img = img;
	// window->coords = coords;
	// window->viewport = viewport;
}