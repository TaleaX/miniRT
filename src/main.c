#include "miniRT.h"
#include "vector.h"
#include "room.h"


static mlx_image_t* img;

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
}

// static uint32_t colorSphere (Vec2 coord, Sphere sphere) {

// 	// t²d² + 2td(O-C) - 2AC + C² + A² - r² 
// 	co
// 	Vec3 rayOrigin = {0.0, 0.0, 3.0};
// 	Vec3 rayDirection = {coord.x, coord.y, -1.0};
// 	sphere.changeRadius(&sphere, 0.5);
// 	//vec3_normalize(&rayDirection); // brauche ich das?
// 	double a = dot_produkt(rayDirection, rayDirection);
// 	double b = 2.0 * (dot_produkt(rayOrigin, rayDirection) - dot_produkt(sphere.center, rayDirection)); 
// 	double c = -2*dot_produkt(rayOrigin, sphere.center) + dot_produkt(sphere.center, sphere.center) + dot_produkt(rayOrigin, rayOrigin) - sphere.radius * sphere.radius;


// 	Vec3 test = vec3_subtraction(rayOrigin, sphere.center);
// 	double discriminant = b * b - 4.0 * a * c;
// 	if (discriminant < 0.0) {
// 		Vec4 colors = {0, 0, 0, 1};
// 		return (get_rgba(colors));
// 	}
// 	Vec4 colors = {0, 0, 0, 1};
// 	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	double t2 = (-b - sqrt(discriminant)) / (2.0 * a);
	
// 	// Vec3 hitPos1;
// 	// hitPos1.x = rayOrigin.x + rayDirection.x * t1;
// 	// hitPos1.y = rayOrigin.y + rayDirection.y * t1;
// 	// hitPos1.z = rayOrigin.z + rayDirection.z * t1;

// 	// we use the second hitpoint cause its the closer one
// 	Vec3 hitPos2;
// 	hitPos2.x = rayOrigin.x + rayDirection.x * t2;
// 	hitPos2.y = rayOrigin.y + rayDirection.y * t2;
// 	hitPos2.z = rayOrigin.z + rayDirection.z * t2;
// 	hitPos2.length = length;
// 	hitPos2.normalize = normalize;

// 	Vec3 lightDir;

// 	//lightDir = {1, 1, 1, length, normalize};
// 	initVec3(&lightDir, 1, 1, 1);
// 	hitPos2.normalize(&hitPos2);
// 	lightDir.normalize(&lightDir);
// 	// vec3_normalize(&hitPos2);
// 	// vec3_normalize(&lightDir);

// 	double d = fmax(dot_produkt(hitPos2, lightDir), 0.0);
// 	// hitPos2.x = (hitPos2.x < 0) ? 0 : ((hitPos2.x > 255) ? 255 : hitPos2.x);
// 	// hitPos2.y = (hitPos2.y < 0) ? 0 : ((hitPos2.y > 255) ? 255 : hitPos2.y);
// 	// hitPos2.z = (hitPos2.z < 0) ? 0 : ((hitPos2.z > 255) ? 255 : hitPos2.z);
// 	// Vec4 sphereColor = {hitPos2.x, hitPos2.y, hitPos2.z, 1.0};
// 	Vec4 sphereColor = {hitPos2.x * 0.5 + 0.5, hitPos2.y * 0.5 + 0.5, hitPos2.z * 0.5 + 0.5, 1.0};
// 	// Vec4 sphereColor = {0.9, 0.3, 0.85 , 1.0};
// 	sphereColor.r *= d;
// 	sphereColor.g *= d;
// 	sphereColor.b *= d;
// 	return (get_rgba(sphereColor));
// }

void colorRoom(Room room, Window window) {
	int	i;

	i = 0;
	// printf("okay\n");
	testColor(window, room.sphere);
	// room.sphere[0].colorSphere(&room.sphere[0], window);
	// while (i < 4) {
	// 	// printf("sphere %d x %f y %f z %f\n", i, room.sphere[i].center.x, room.sphere[i].center.y, room.sphere[i].center.z);
	// 	room.sphere[i].color(&room.sphere[i], window);
	// 	//room.plane[i].color(&room.plane[0], window);
	// 	++i;
	// }
}

int32_t	main(void)
{
	mlx_t*	mlx;
	Room	room;
	Vec2 	coord;
	Window	window;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(img->pixels, 0, img->width * img->height * sizeof(int));
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	initRoom(&room);
	// initWindow(&window, img);
	window.img = img;
	for (double y = 0; y < HEIGHT; ++y){
		for (double x = 0; x < WIDTH; ++x){
			// window.viewport.changeCoords(&window.viewport, x * VH / WIDTH, y * VW / HEIGHT, 1);
			// window.viewport.y = y * VW / HEIGHT;//((y / HEIGHT));// * 2.0 - 1.0) * -1;
			// window.viewport.x = x * VH / WIDTH;//((x / WIDTH)); //* 2.0 - 1.0) * -1;
			window.x = x;
			window.y = y;
			window.coords.x = (2 * x * VW / WIDTH - VW);
			window.coords.y = (2 * y * VH / HEIGHT - VH) * -1;
			// windowSetVars(&window, x, y);
			colorRoom(room, window);
		}
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}