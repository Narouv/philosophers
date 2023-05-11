/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:35:31 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/10 20:01:50 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		*pt;
	int				fl;
	int				fr;
	int				pn;
	void			*p_to_info;
	unsigned long	eat_ts;
	unsigned long	sleep_ts;
	int				n_eat;
}	t_philo;

typedef struct s_info
{
	t_philo			**philo;
	sem_t 			*utensils;
	unsigned long	starttime;
	unsigned long	elapsed;
	sem_t			writing;
	int				num_philo;
	int				stop;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				eat_num;
	int				all_ate;
}	t_info;

int		ft_atoi(const char *str);
void	*philo_cycle(void *i);
void	cleanup(void);

#endif
