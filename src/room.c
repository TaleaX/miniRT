#include "room.h"

void	changeRadius(void* self, double radius) {
	Sphere* this;

	this = self;
	this->radius = radius;
}

void	changeCenter(void* self, double x, double y, double z){
	Sphere*	this;

	this = self;
	this->center.x = x;
	this->center.y = y;
	this->center.z = z;
}

