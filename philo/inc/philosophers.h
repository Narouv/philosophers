/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:35:31 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 20:15:33 by rnauke           ###   ########.fr       */
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
	pthread_t		*pt;
	int				fl;
	int				fr;
	int				pn;
	void			*p_to_info;
	unsigned long	eat_ts;
	unsigned long	sleep_ts;
	int				n_eat;
	pthread_mutex_t	*eating;
}	t_philo;

typedef struct s_info
{
	t_philo			**philo;
	pthread_mutex_t	*utensils;
	unsigned long	st;
	unsigned long	elapsed;
	pthread_mutex_t	writing;
	int				num_philo;
	int				stop;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				eat_num;
	int				all_ate;
}	t_info;

int				ft_atoi(const char *str);
void			*philo_cycle(void *i);
void			ft_msleep(t_info *info, unsigned long ms);
void			print(t_philo *p, char *str);
void			check_stop(t_info *info);
unsigned long	timestamp(void);
void			cleanup(t_info *info);

#endif
