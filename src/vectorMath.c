#include "vector.h"

double dot_produkt(Vec3 v1, Vec3 v2) {
	return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double length(void* self) {
	Vec3*	this;

	this = self;
	return (sqrt(this->x * this->x + this->y * this->y + this->z * this->z));
}

void	normalize(void* self) {
	Vec3*	this;
	double length;

	this = self;
	length = this->length(this);
	this->x /= length; 
	this->y /= length; 
	this->z /= length; 
}

void	hitPos(void* self, Vec3 rayOrigin, Vec3 rayDirection, double t) {
	Vec3*	this;

	this = self;
	this->x = rayOrigin.x + rayDirection.x * t;
	this->y = rayOrigin.y + rayDirection.y * t;
	this->z = rayOrigin.z + rayDirection.z * t;
}

Vec3 vec3_subtraction(Vec3  vec1, Vec3 vec2) {
	Vec3 v;

	v.x = vec2.x - vec1.x;
	v.y = vec2.y - vec1.y;
	v.z = vec2.z - vec1.z;

	return (v);
}