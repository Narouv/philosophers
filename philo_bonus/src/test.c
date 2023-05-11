#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

unsigned long	get_elapsed()
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int main(void)
{
	unsigned long i = get_elapsed();
	sleep(1);
	printf("%lu", get_elapsed() - i);
}
