#include <time.h>
#include <stdlib.h>

double	random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}