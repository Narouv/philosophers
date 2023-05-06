/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:46:34 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/05 16:31:59 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	graveyard(t_philo **p, int tombs)
{
	while (tombs >= 0)
	{
		pthread_detach(*p[tombs]->pt)
		free(*p[tombs]->pt)
	}
	free(p);
}

void	dishwasher(pthread_mutex_t *cutlery, int amount)
{
	while (amount >= 0)
	{
		pthread_mutex_unlock(&cutlery[amount]);
		pthread_mutex_destroy(&cutlery[amount]);
		free(cutlery[amount--]);
	}
	free(cutlery);	
}

void	cleanup(t_info *info)
{
	graveyard(info->philo)
	dishwasher(info->utensils);
	free(info);
	// exit(0);
}
