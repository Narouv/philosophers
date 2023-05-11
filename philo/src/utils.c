/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:23:31 by rnauke            #+#    #+#             */
/*   Updated: 2023/05/11 17:22:05 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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

unsigned long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	print(t_philo *p, char *str)
{
	unsigned long	time;
	t_info			*info;

	info = p->p_to_info;
	pthread_mutex_lock(&info->writing);
	time = info->starttime;
	if (!info->stop)
		printf("%lu %i %s", timestamp() - time, p->pn, str);
	pthread_mutex_unlock(&info->writing);
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
