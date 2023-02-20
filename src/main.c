
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include "miniRT.h"
#include "vectorMath.h"
#include "MLX42/MLX42.h"
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
	uint8_t g = (uint8_t)(255.0 * colors.b);
	uint8_t b = (uint8_t)(255.0 * colors.g);
	uint8_t a = (uint8_t)(255.0 * colors.a);
	
	// return (a << 24) | (b << 16) | (g << 8) | r;
	return (r << 24 | g << 16 | b << 8 | a);
}



static uint32_t color (Vec2 coord, double radius, Vec3 center) {
	// int r = 255.999 * coord.x;
	// int b = 255.999 * coord.y;
	// int g = 100;
	// int a = 255;

	// t²d² + 2td(O-C) - 2AC + C² + A² - r² 
	Vec3 rayOrigin = {0.0, 0.0, 1.0};
	Vec3 rayDirection = {coord.x, coord.y, -1.0};
	double a = dot_produkt(rayDirection, rayDirection);
	double b = 2.0 * (dot_produkt(rayOrigin, rayDirection) - dot_produkt(center, rayDirection)); 
	double c = -2*dot_produkt(rayOrigin, center) + dot_produkt(center, center) + dot_produkt(rayOrigin, rayOrigin) - radius * radius;


	Vec3 test = vec3_subtraction(rayOrigin, center);
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

	Vec3 lightDir = {-1, -1, 1};
	vec3_normalize(&hitPos2);
	vec3_normalize(&lightDir);

	double d = fmax(dot_produkt(hitPos2, lightDir), 0.0);
	// Vec4 color = {hitPos2.x * 0.5 + 0.5, hitPos2.y * 0.5 + 0.5, hitPos2.z * 0.5 + 0.5, 1.0};	
	Vec4 sphereColor = {0.0, 1.0, 0.0 , 1.0};
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
	double radius = 0.5;
	Vec2 coord;
	Vec3 center = {0.0, 0.0, 0.0};
	for (double y = 0; y < HEIGHT; ++y){
		for (double x = 0; x < WIDTH; ++x){
			coord.y = (y / HEIGHT) * 2.0 - 1.0;
			coord.x = (x / WIDTH) * 2.0 - 1.0;
			mlx_put_pixel(img,x, y, color(coord, radius, center));
		}
	}
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}