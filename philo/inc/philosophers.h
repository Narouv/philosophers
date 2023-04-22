/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:35:31 by rnauke            #+#    #+#             */
/*   Updated: 2023/04/22 11:26:53 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	*philo;
	int			sleep_td;
	int			eat_td;
}	t_philo;

typedef struct s_info
{
	t_philo			*pps;
	pthread_mutex_t **utensils;
	struct timeval	time;
	unsigned int	time_delta;
	unsigned int	elapsed;
	int				philo_num;
	int				sleep_time;
	int				eat_time;
	int				death_time;
	int				num_eat;
	int				death;
}	t_info;

#endif
