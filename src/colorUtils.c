#include "vector.h"
#include "miniRT.h"

uint32_t	get_rgba(Vec4 colors)
{	uint8_t r = (uint8_t)(255.0 * colors.r);
	uint8_t g = (uint8_t)(255.0 * colors.g);
	uint8_t b = (uint8_t)(255.0 * colors.b);
	uint8_t a = (uint8_t)(255.0 * colors.a);
	
	// return (a << 24) | (b << 16) | (g << 8) | r;
	return (r << 24 | g << 16 | b << 8 | a);
}