#include "room.h"

void	initSphere(void* self, Vec3 center, double radius) {
	Sphere* this = self;
	this->center = center;
	this->radius = radius;
	this->changeRadius = changeRadius;
	
}
void	initCamera(void* self, Vec3 rayOrigin, Vec3 rayDirection) {
	Camera*	this = self;
	this->rayOrigin = rayOrigin;
	this->rayDirection = rayDirection;
}