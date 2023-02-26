#ifndef MINIRT_H
# define MINIRT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# include <math.h>
# include "vector.h"
# include "MLX42/MLX42.h"
# define WIDTH 800
# define HEIGHT 800
# define VH 2
# define VW 2


typedef struct window Window;
typedef struct viewport Viewport;


void	windowSetVars(void* self, double x, double y);

struct window { 
	mlx_image_t*	img;
	int				x;
	int				y;
	// Camera			camera;
	Vec2			coords;
};

void	initWindow(Window* window, mlx_image_t* img);

// struct viewport {
// 	double	x;
// 	double	y;
// 	double	z;
// 	void	(*changeCoords)(view);
// };

#endif