/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/11 19:41:24 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	spawn_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(info->philo[i]->pt, NULL, philo_cycle, info->philo[i]);
		i++;
	}
}

void	set_table(t_info *info)
{
	sem_unlink("wtfork");
	info->utensils = sem_open("wtfork", O_CREAT, S_IRWXU, info->num_philo);
}

void	assign_seats(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i]->fr = i;
		info->philo[i]->fl = (i + 1) % info->num_philo;
		i++;
	}
}

void	init_info(t_info *info, int argc, char **argv)
{
	int	i;

	info->starttime = timestamp();
	info->num_philo = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->eat_num = -1;
	if (argc == 6)
		info->eat_num = ft_atoi(argv[5]);
	info->stop = 0;
	info->philo = malloc(sizeof(t_philo *) * info->num_philo);
	set_table(info);
	i = 0;
	while (i < info->num_philo)
	{
		info->philo[i] = malloc(sizeof(t_philo));
		info->philo[i]->pt = malloc(sizeof(pthread_t));
		info->philo[i]->pn = i + 1;
		info->philo[i]->p_to_info = info;
		info->philo[i]->n_eat = 0;
		info->philo[i]->eat_ts = timestamp();
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	*info;

	if (argc < 5 || argc > 6)
	{
		printf("Too many or too little args\nShould be 4 or 5\n");
		return (1);
	}
	info = malloc(sizeof(t_info));
	init_info(info, argc, argv);
	sem_unlink("writing");
	info->writing = sem_open("writing", O_CREAT, S_IRWXU, 1);
	assign_seats(info);
	spawn_philosophers(info);
	while (!info->stop)
	{
		check_stop(info);
	}
	cleanup(info);
	return (0);
}
