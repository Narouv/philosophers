/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/04/15 19:53:29 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	lay_table(pthread_mutex_t **forks)
{
	
}

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

void	start(void *param)
{
	t_info *info;

	info = param;
	usleep(50);
	info->time_delta = 10000;
	gettimeofday(&info->time, NULL);
	printf("hi there ;)");
}

int main(int argc, char **argv)
{
	t_info *info;
	pthread_t thread;
	
	// if (argc < 5 || argc > 6)
	// {
	// 	printf("wrong number of args");
	// 	return (1);
	// }
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
		// cleanup(info, "malloc fail");
	pthread_create(&thread, NULL, (void *)start, (void *)info);
	// start();
	while (1)
	{
		get_time_delta(info);
		if (info->time_delta > 1)
		{
			
			pthread_kill(thread, 0);
			printf("detached");
			break ;
		}
		else
			printf(" ");
	}
	return (0);
}