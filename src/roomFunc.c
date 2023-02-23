#include "room.h"

void	changeRadius(void* self, double radius) {
	Sphere* this = self;
	this->radius = radius;
}