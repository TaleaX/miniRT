#include <time.h>
#include <stdlib.h>

double	random_double(void)
{
	return ((double)rand() / ((double)RAND_MAX + 1.0));
}

double	random_min_max(double min, double max)
{
	return (random_double() * (max - min) + min);
}