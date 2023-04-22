/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/04/22 11:32:01 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	lay_table(pthread_mutex_t **forks)
{
	
}

void	spawn_philosophers(t_info *info)

void	seat_philosophers(pthread_t **philos)
{
	
}

void	get_time_delta(t_info *info)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	info->time_delta = (t.tv_sec - info->time.tv_sec) * 1000000 + t.tv_usec - info->time.tv_usec;
}

void	init_info(t_info *info)
{
	gettimeofday(&info->time, NULL);
}

void	*start(void *param)
{
	t_info *info;

	info = param;
	usleep(25);
	printf("hi there ;)");
}

void	*timer(void *param)
{
	long long	t;
	t_info		*info

	info = param;
	t = info->elapsed;
	while (1)
	{
		if (t - )
		usleep(*(int *)time);
	}
	return (NULL);
}

void	*philosopher_grab_left(void *param)
{
	t_info		*info;
	int			pn;

	info = param;
	pn = ++info->philo_num;
	// fork access: pn && pn-1
	// grab left fork
	// if left fork in hand and right fork is available -> grab right fork and eat
	// eat
	printf("%i - %i is eating spaghetti at %fcm/s", info->elapsed, pn, (info->eat_time/1000));
	// sleep
	printf("%i - %i is sleeping", info->elapsed, pn);
	// try to eat
}

int main(int argc, char **argv)
{
	t_info *info;
	pthread_t t1;
	pthread_t t2;

	// if (argc < 5 || argc > 6)
	// {
	// 	printf("wrong number of args");
	// 	return (1);
	// }
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
		// cleanup(info, "malloc fail");
	pthread_create(&t1, NULL, , (void *)info);
	gettimeofday(&info->time, NULL);
	usleep(20);
	pthread_detach(t1);
	printf("detached");
	return (0);
}