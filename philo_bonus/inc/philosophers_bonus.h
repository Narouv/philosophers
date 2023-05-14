/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:35:31 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 18:25:34 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h> 
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_philo
{
	pid_t			pt;
	int				fl;
	int				fr;
	int				pn;
	struct s_info	*p_to_info;
	unsigned long	eat_ts;
	unsigned long	sleep_ts;
	int				n_eat;
	pthread_t		tid;
}	t_philo;

typedef struct s_info
{
	t_philo			**philo;
	sem_t			*utensils;
	unsigned long	starttime;
	unsigned long	elapsed;
	sem_t			*writing;
	sem_t			*eating;
	int				num_philo;
	int				stop;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				eat_num;
	int				all_ate;
	int				start;
}	t_info;

int				ft_atoi(const char *str);
void			philo_cycle(void *ptp);
void			ft_msleep(t_info *info, unsigned long ms);
void			print(t_philo *p, char *str);
void			*check_stop(void *ptp);
unsigned long	timestamp(void);
void			cleanup(t_info *info);

#endif
