/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:02:46 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 20:11:10 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	eat(t_philo *p)
{
	t_info	*info;

	info = p->p_to_info;
	sem_wait(info->utensils);
	print(p, "has taken a fork\n");
	sem_wait(info->utensils);
	print(p, "has taken a fork\n");
	sem_wait(info->eating);
	p->eat_ts = timestamp();
	sem_post(info->eating);
	print(p, "is eating\n");
	ft_msleep(info, info->eat_time);
	p->n_eat++;
	sem_post(info->utensils);
	sem_post(info->utensils);
}

void	philo_sleep(t_philo *p)
{
	t_info	*info;

	info = p->p_to_info;
	print(p, "is sleeping\n");
	ft_msleep(info, info->sleep_time);
	print(p, "is thinking\n");
}

void	philo_cycle(void *ptp)
{
	t_philo	*p;
	t_info	*info;

	p = (t_philo *)ptp;
	info = p->p_to_info;
	p->eat_ts = timestamp();
	pthread_create(&p->tid, NULL, check_stop, p);
	if (p->pn % 2 == 0)
		ft_msleep(info, info->eat_time);
	while (!info->stop)
	{
		eat(p);
		if (p->n_eat >= info->eat_num && info->eat_num != -1)
			break ;
		philo_sleep(p);
	}
	pthread_join(p->tid, NULL);
	exit(0);
}

void	*check_stop(void *ptp)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ptp;
	info = philo->p_to_info;
	while (!info->stop)
	{
		usleep(500);
		sem_wait(info->eating);
		if (timestamp() - philo->eat_ts > info->die_time)
		{
			info->stop = 1;
			printf("%lu %i died\n", timestamp() - info->starttime, philo->pn);
		}
		sem_post(info->eating);
		if (info->stop)
			break ;
		if (philo->n_eat >= info->eat_num && info->eat_num != -1)
			break ;
	}
	return (NULL);
}
