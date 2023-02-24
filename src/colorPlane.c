#include "room.h"

void	colorPlane(void* self, Window window) {
	Sphere*	this;
	Vec3	rayOrigin = {0.0, 0.0, 1.0};
	Vec3	rayDirection = window.viewport;
	double	discriminant;
	Vec3*	hitPos;

	//vec3_normalize(&rayDirection); // brauche ich das?
	this = self;
	hitPos = getHitPoint(*this, rayOrigin, rayDirection);
	if (hitPos == NULL) {
		// Vec4 colors = {0, 0, 0, 1};
		// mlx_put_pixel(window.img, window.x, window.y, 0x000000ff);
	} else
		colorSphere(*hitPos, window);
	free(hitPos);
}
