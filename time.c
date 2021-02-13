#include "philosophers.h"

unsigned long get_time(void)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec * 0.001));
}
