/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:02:46 by rnauke            #+#    #+#             */
/*   Updated: 2023/04/28 15:51:50 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philo_life(void *phi)
{
	t_philo		*philo;
	pthread_t	t;

	philo = (t_philo *)phi;
	if (philo->n % 2 == 0)
		ft_sleep(philo->info->t_eat);
	while (!is_dead(philo, 0))
	{
		take_fork(philo);
		philo_eat(philo);
		if (philo->m_count == philo->info->n_eat)
		{
			if (++philo->info->philo_eat == philo->info->n_philo)
			{
				is_dead(philo, 2);
			}
			return (NULL);
		}
	}
	return (NULL);
}
