/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:46:34 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/11 18:09:16 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	graveyard(t_philo **p, int tombs)
{
	while (tombs > 0)
	{
		pthread_join(*p[tombs - 1]->pt, NULL);
		free(p[tombs -1]->pt);
		free(p[tombs -1]);
		tombs--;
	}
	free(p);
}

void	dishwasher(pthread_mutex_t *cutlery, int amount)
{
	while (amount > 0)
	{
		pthread_mutex_unlock(&cutlery[amount - 1]);
		pthread_mutex_destroy(&cutlery[amount - 1]);
		amount--;
	}
	free(cutlery);
}

void	cleanup(t_info *info)
{
	dishwasher(info->utensils, info->num_philo);
	graveyard(info->philo, info->num_philo);
	pthread_mutex_destroy(&info->writing);
	free(info);
}
