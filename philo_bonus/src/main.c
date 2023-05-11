/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:34:19 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/09 23:33:47 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	cleanup(t_info *info)
{
	free(info);
	exit(0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	sign = 1;
	n = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * sign);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	spawn_philosophers(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(info->philo[i]->pt, NULL, philo_cycle, info->philo[i]);
		i++;
	}
	// printf("spawned %i philos\n", i);
}

unsigned long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	set_table(t_info *info)
{
	int	i;

	i = 0;
	info->utensils = malloc(sizeof(pthread_mutex_t) * info->num_philo);
	while (i < info->num_philo)
		pthread_mutex_init(&info->utensils[i++], NULL);
}

// i++ so while loop doesnt run
void	assign_seats(t_info *info)
{
	int	i;

	i = 0;
	// if (info->num_philo == 1)
	// {
	// 	info->philo[0]->fr = &info->utensils[0];
	// 	info->philo[0]->fl = &info->utensils[0];
	// 	i++;
	// }
	while (i < info->num_philo)
	{
		// printf("i %i, pn %i, c %i\n", i, info->num_philo, (i + 1) % info->num_philo);
		info->philo[i]->fr = i;
		// printf("fr %i\n", info->philo[i]->fr);
		info->philo[i]->fl = (i + 1) % info->num_philo;
		// printf("fl %i\n", info->philo[i]->fl);
		i++;
	}

}

void	init_info(t_info *info, int argc, char **argv)
{
	int i;

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
	// pthread_mutex_init(&info->writing, NULL);
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
	assign_seats(info);
}

void	print(t_philo *p, char *str)
{
	unsigned long	time;
	t_info		*info;

	info = p->p_to_info;
	// pthread_mutex_lock(&info->writing);
	time = info->starttime;
	if (!info->stop)
		printf("%lu %i %s", timestamp() - time, p->pn, str);
	// pthread_mutex_unlock(&info->writing);
}

void	ft_msleep(t_info *info, unsigned long ms)
{
	unsigned long	s;
	
	s = timestamp();
	while (timestamp() - s < ms)
	{
		if (info->stop)
			break ;
		usleep(10);
	}
}

void	eat(t_philo *p)
{
	t_info	*info;

	info = p->p_to_info;
	pthread_mutex_lock(&info->utensils[p->fr]);
	print(p, "has taken a fork\n");
	pthread_mutex_lock(&info->utensils[p->fl]);
	print(p, "has taken a fork\n");
	p->eat_ts = timestamp();
	print(p, "is eating\n");
	ft_msleep(info, info->eat_time);
	p->n_eat++;
	pthread_mutex_unlock(&info->utensils[p->fr]);
	pthread_mutex_unlock(&info->utensils[p->fl]);
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

int main(int argc, char **argv)
{
	t_info	*info;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of args");
		return (1);
	}
	info = malloc(sizeof(t_info));
	init_info(info, argc, argv);
	spawn_philosophers(info);
	while (!info->stop)
	{
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
			if (info->stop)
				break ;
			i++;
		}
		i = 0;
		while (info->eat_num != -1 && i < info->num_philo && info->philo[i]->n_eat >= info->eat_num)
			i++;
		if (i == info->num_philo)
			info->all_ate++;
	}
	cleanup(info);
	return (0);
}
