/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:46:34 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 20:11:18 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	graveyard(t_philo **p, int tombs)
{
	int		i;
	int		r;
	t_info	*info;

	i = 0;
	info = p[0]->p_to_info;
	while (i < info->num_philo)
	{
		waitpid(-1, &r, 0);
		if (r != 0)
		{
			i = -1;
			while (++i < info->num_philo)
				kill(p[i]->pt, 15);
			break ;
		}
		i++;
	}
	while (tombs > 0)
	{
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
	graveyard(info->philo, info->num_philo);
	dishwasher(info->utensils, info->num_philo);
	sem_unlink("writing");
	sem_unlink("eating");
	sem_close(info->eating);
	sem_close(info->writing);
	free(info);
	exit(0);
}
