#include <time.h>
#include <stdlib.h>

double	random_double(void)
{
	return ((double)rand() / (RAND_MAX));
}

double	random_min_max(double min, double max)
{
	return (random_double() * (max - min) + min);
}