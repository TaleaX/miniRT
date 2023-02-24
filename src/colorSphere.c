# include "vector.h"
# include "room.h"
# include "utils.h"

static Vec3*	getHitPoint(Sphere sphere, Vec3 rayOrigin, Vec3 rayDirection){
	double	a;
	double	b;
	double	c;
	double	discriminant;
	Vec3*	hitPos;

	a = dot_produkt(rayDirection, rayDirection);
	b = 2.0 * (dot_produkt(rayOrigin, rayDirection) - dot_produkt(sphere.center, rayDirection));
	c = -2 * dot_produkt(rayOrigin, sphere.center) + dot_produkt(sphere.center, sphere.center) + dot_produkt(rayOrigin, rayOrigin) - sphere.radius * sphere.radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (NULL);
	hitPos = calloc(1, sizeof(Vec3));
	initVec3(hitPos, 0, 0, 0);
	hitPos->hitPos(hitPos, rayOrigin, rayDirection, (-b - sqrt(discriminant)) / (2.0 * a));
	return (hitPos);
}

// static void initHitPoint(double discriminant) {
// 	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
// }
// Vec3 hitPos1;
	// hitPos1.x = rayOrigin.x + rayDirection.x * t1;
	// hitPos1.y = rayOrigin.y + rayDirection.y * t1;
	// hitPos1.z = rayOrigin.z + rayDirection.z * t1;

	// we use the second hitpoint cause its the closer one

static void	color(Vec3 hitPos, Window window) {
	Vec4	sphereColor;
	Vec3	lightDir;
	double	d;

	initVec3(&lightDir, 1, 1, 1);
	hitPos.normalize(&hitPos);
	lightDir.normalize(&lightDir);
	d = fmax(dot_produkt(hitPos, lightDir), 0.0);
	hitPos.x = (hitPos.x < 0) ? 0 : ((hitPos.x > 255 ? 255 : hitPos.x));
	hitPos.y = (hitPos.y < 0) ? 0 : ((hitPos.y > 255 ? 255 : hitPos.y));
	hitPos.z = (hitPos.z < 0) ? 0 : ((hitPos.z > 255 ? 255 : hitPos.z));

	sphereColor.r = (hitPos.x);// * 0.5 + 0.5);// * d;
	sphereColor.g = (hitPos.y);// * 0.5 + 0.5);// * d;
	sphereColor.b = (hitPos.z);// * 0.5 + 0.5);// * d;
	sphereColor.a = 1.0;
	mlx_put_pixel(window.img, window.x, window.y, get_rgba(sphereColor));
}

void	colorSphere(void* self, Window window) {
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
		color(*hitPos, window);
	free(hitPos);
}
