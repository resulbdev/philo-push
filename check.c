/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resulbozdemir <resulbozdemir@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:41:00 by rbozdemi          #+#    #+#             */
/*   Updated: 2023/03/05 23:04:21 by resulbozdem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: argument is not a number\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	dead_philo(t_philo *philo, int i, long long int time)
{
	if (time > philo[i].die_time)
	{
		printf("%lldms %d died\n", time, philo[i].id + 1);
		*philo[i].is_dead = 1;
		return (1);
	}
	return (0);
}

int	check_null(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!argv[i][0])
			return (0);
		i++;
	}
	return (1);
}

int	check_eat(t_philo *philo)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	if (philo->must_eat != -1)
	{
		while (j < philo->philo_count)
			result += philo[(j)++].eat_count;
		if (result == philo->philo_count * philo->must_eat)
		{
			*philo->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

void	check_dead(t_philo *philo)
{
	long long int	time;
	int				i;

	i = 0;
	while (i < philo->philo_count)
	{
		pthread_mutex_lock(philo->print);
		time = now_time() - philo[i].last_eat;
		if (dead_philo(philo, i, time) || check_eat(philo))
		{
			break ;
		}
		i++;
		pthread_mutex_unlock(philo->print);
	}
}
