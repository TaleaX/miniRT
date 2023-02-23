#ifndef MINIRT_H
# define MINIRT_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
# include <math.h>
# include "vector.h"
#include "MLX42/MLX42.h"

typedef struct window { 
	mlx_image_t*	img;
	int				x;
	int				y;
	Vec2			coord;
} Window;


#endif