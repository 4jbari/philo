#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		perror("gettimeofday");
		return (-1);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
