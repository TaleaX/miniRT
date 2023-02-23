
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "miniRT.h"
#include "vectorMath.h"
#include "MLX42/MLX42.h"
#include "room.h"
#define WIDTH 800
#define HEIGHT 800

static mlx_image_t* img;

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
}

static uint32_t	get_rgba(Vec4 colors)
{	uint8_t r = (uint8_t)(255.0 * colors.r);
	uint8_t g = (uint8_t)(255.0 * colors.g);
	uint8_t b = (uint8_t)(255.0 * colors.b);
	uint8_t a = (uint8_t)(255.0 * colors.a);
	
	// return (a << 24) | (b << 16) | (g << 8) | r;
	return (r << 24 | g << 16 | b << 8 | a);
}



static uint32_t color (Vec2 coord, Sphere sphere) {
	// int r = 255.999 * coord.x;
	// int b = 255.999 * coord.y;
	// int g = 100;
	// int a = 255;

	// t²d² + 2td(O-C) - 2AC + C² + A² - r² 
	Vec3 rayOrigin = {0.0, 0.0, 3.0};
	Vec3 rayDirection = {coord.x, coord.y, -1.0};
	sphere.changeRadius(&sphere, 0.5);
	//vec3_normalize(&rayDirection); // brauche ich das?
	double a = dot_produkt(rayDirection, rayDirection);
	double b = 2.0 * (dot_produkt(rayOrigin, rayDirection) - dot_produkt(sphere.center, rayDirection)); 
	double c = -2*dot_produkt(rayOrigin, sphere.center) + dot_produkt(sphere.center, sphere.center) + dot_produkt(rayOrigin, rayOrigin) - sphere.radius * sphere.radius;


	Vec3 test = vec3_subtraction(rayOrigin, sphere.center);
	double discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0) {
		Vec4 colors = {0, 0, 0, 1};
		return (get_rgba(colors));
	}
	Vec4 colors = {0, 0, 0, 1};
	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
	
	// Vec3 hitPos1;
	// hitPos1.x = rayOrigin.x + rayDirection.x * t1;
	// hitPos1.y = rayOrigin.y + rayDirection.y * t1;
	// hitPos1.z = rayOrigin.z + rayDirection.z * t1;

	// we use the second hitpoint cause its the closer one
	Vec3 hitPos2;
	hitPos2.x = rayOrigin.x + rayDirection.x * t2;
	hitPos2.y = rayOrigin.y + rayDirection.y * t2;
	hitPos2.z = rayOrigin.z + rayDirection.z * t2;

	Vec3 lightDir = {1, 1, 1};
	vec3_normalize(&hitPos2);
	vec3_normalize(&lightDir);

	double d = fmax(dot_produkt(hitPos2, lightDir), 0.0);
	// hitPos2.x = (hitPos2.x < 0) ? 0 : ((hitPos2.x > 255) ? 255 : hitPos2.x);
	// hitPos2.y = (hitPos2.y < 0) ? 0 : ((hitPos2.y > 255) ? 255 : hitPos2.y);
	// hitPos2.z = (hitPos2.z < 0) ? 0 : ((hitPos2.z > 255) ? 255 : hitPos2.z);
	// Vec4 sphereColor = {hitPos2.x, hitPos2.y, hitPos2.z, 1.0};
	Vec4 sphereColor = {hitPos2.x * 0.5 + 0.5, hitPos2.y * 0.5 + 0.5, hitPos2.z * 0.5 + 0.5, 1.0};
	// Vec4 sphereColor = {0.9, 0.3, 0.85 , 1.0};
	sphereColor.r *= d;
	sphereColor.g *= d;
	sphereColor.b *= d;
	return (get_rgba(sphereColor));
}

int32_t	main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(EXIT_FAILURE);

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(img->pixels, 0, img->width * img->height * sizeof(int));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Vec3 rayOrigin = {0, 0, 2};
	double radius = 1;
	Vec2 coord;
	Vec3 center = {0.0, 0.0, 0.0};
	Sphere sphere;
	initSphere(&sphere, center, radius);
	for (double y = 0; y < HEIGHT; ++y){
		for (double x = 0; x < WIDTH; ++x){
			coord.y = (y / HEIGHT) * 2.0 - 1.0;
			coord.x = (x / WIDTH) * 2.0 - 1.0;
			mlx_put_pixel(img, x, y, color(coord, sphere));
		}
	}
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}