/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:02:46 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/11 18:53:52 by rnauke           ###   ########.fr       */
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
	p->eat_ts = timestamp();
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
		philo_sleep(p);
	}
	return (p);
}

void	check_stop(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		if (timestamp() - info->philo[i]->eat_ts > info->die_time)
		{
			if (timestamp() - info->philo[i]->eat_ts > info->die_time)
			{
				print(info->philo[i], "died\n");
				info->stop = 1;
			}
		}
		if (info->eat_num > 0 && info->all_ate >= info->eat_num)
			info->stop = 1;
		i++;
	}
	i = 0;
	while (info->eat_num != -1 && i < info->num_philo
		&& info->philo[i]->n_eat >= info->eat_num)
		i++;
	if (i == info->num_philo)
		info->all_ate++;
}
