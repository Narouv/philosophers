/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/14 20:38:32 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
	int	i;

	i = 0;
	info->utensils = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	while (i < info->num_philo)
		pthread_mutex_init(&info->utensils[i++], NULL);
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

	info->st = timestamp();
	info->num_philo = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	info->eat_num = -1;
	if (argc == 6)
		info->eat_num = ft_atoi(argv[5]);
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
		info->philo[i]->eating = malloc(sizeof(pthread_mutex_t));
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
	info->stop = 0;
	pthread_mutex_init(&info->writing, NULL);
	assign_seats(info);
	spawn_philosophers(info);
	check_stop(info);
	cleanup(info);
	return (0);
}
