/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:46:34 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/13 21:00:05 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	graveyard(t_philo **p, int tombs)
{
	while (tombs > 0)
	{
		waitpid(p[tombs -1]->pt, NULL, WUNTRACED);
		free(p[tombs -1]);
		tombs--;
	}
	free(p);
}

void	dishwasher(sem_t *cutlery, int amount)
{
	while (amount > 0)
	{
		sem_post(cutlery);
		sem_post(cutlery);
		amount--;
	}
	sem_unlink("wtfork");
	sem_close(cutlery);
}

void	cleanup(t_info *info)
{
	dishwasher(info->utensils, info->num_philo);
	graveyard(info->philo, info->num_philo);
	sem_unlink("writing");
	sem_unlink("eating");
	sem_close(info->eating);
	sem_close(info->writing);
	free(info);
}
