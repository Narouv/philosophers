/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:02:46 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 20:20:51 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	eat(t_philo *p)
{
	t_info	*info;

	info = p->p_to_info;
	pthread_mutex_lock(&info->utensils[p->fr]);
	print(p, "has taken a fork\n");
	pthread_mutex_lock(&info->utensils[p->fl]);
	print(p, "has taken a fork\n");
	print(p, "is eating\n");
	pthread_mutex_lock(p->eating);
	p->eat_ts = timestamp();
	pthread_mutex_unlock(p->eating);
	ft_msleep(info, info->eat_time);
	p->n_eat++;
	pthread_mutex_unlock(&info->utensils[p->fr]);
	pthread_mutex_unlock(&info->utensils[p->fl]);
}

void	*philo_cycle(void *i)
{
	t_philo	*p;
	t_info	*info;

	p = (t_philo *)i;
	info = p->p_to_info;
	if (p->pn % 2 == 0)
		ft_msleep(info, info->eat_time);
	while (!info->stop)
	{
		eat(p);
		print(p, "is sleeping\n");
		ft_msleep(info, info->sleep_time);
		print(p, "is thinking\n");
	}
	return (p);
}

int	died(t_info *in, int i)
{
	in->stop = 1;
	printf("%lu %i died\n", timestamp() - in->st, in->philo[i]->pn);
	return (1);
}

void	check_stop(t_info *info)
{
	int	i;

	while (!info->stop)
	{
		i = 0;
		while (i < info->num_philo)
		{
			pthread_mutex_lock(info->philo[i]->eating);
			if (timestamp() - info->philo[i]->eat_ts > info->die_time)
				if (died(info, i))
					break ;
			pthread_mutex_unlock(info->philo[i]->eating);
			i++;
			usleep(100);
		}
		i = 0;
		while (info->eat_num != -1 && i < info->num_philo
			&& info->philo[i]->n_eat >= info->eat_num)
			i++;
		if (i == info->num_philo)
			info->all_ate++;
		if (info->eat_num > 0 && info->all_ate >= info->eat_num)
			info->stop = 1;
	}
}
