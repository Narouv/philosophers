/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/04/14 16:21:55 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philosophers.h"

void	lay_table(pthread_mutex_t **forks)
{
	
}

void	seat_philosophers(pthread_t **philos)
{
	
}

int main(int argc, char **argv)
{
	t_info *info;
	
	// if (argc < 5 || argc > 6)
	// {
	// 	printf("wrong number of args");
	// 	return (1);
	// }
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
		// cleanup(info, "malloc fail");
// 	lay_table(info->utensils);
// 	seat_philosophers(info->pps);
	gettimeofday(&info->time, 0);
	printf("s: %li\nus: %i\n\n", info->time.tv_sec, info->time.tv_usec);
	gettimeofday(&info->time, 0);
	printf("s: %li\nus: %i\n\n", info->time.tv_sec, info->time.tv_usec);
	gettimeofday(&info->time, 0);
	printf("s: %li\nus: %i\n\n", info->time.tv_sec, info->time.tv_usec);
	gettimeofday(&info->time, 0);
	printf("s: %li\nus: %i\n\n", info->time.tv_sec, info->time.tv_usec);
	gettimeofday(&info->time, 0);
	printf("s: %li\nus: %i\n\n", info->time.tv_sec, info->time.tv_usec);
	
}