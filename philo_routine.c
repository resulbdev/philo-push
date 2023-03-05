/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozdemi <rbozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:41:11 by rbozdemi          #+#    #+#             */
/*   Updated: 2023/03/03 14:41:12 by rbozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_eat_and_sleep(philo))
			break ;
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

int	philo_eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (philo->philo_count == 1)
	{
		ft_usleep(philo->die_time * 2);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(philo->print);
	philo->eat_count++;
	philo->last_eat = now_time();
	pthread_mutex_unlock(philo->print);
	ft_usleep(philo->eat_time);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->sleep_time);
	return (0);
}
