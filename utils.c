/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozdemi <rbozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:41:15 by rbozdemi          #+#    #+#             */
/*   Updated: 2023/03/03 14:41:35 by rbozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	string_to_int(char *str)
{
	int				i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

long long int	now_time(void)
{
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long long int time)
{
	long long int	start;

	start = now_time();
	while (now_time() - start < time)
		usleep(100);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print);
	if (*philo->is_dead != 1)
		printf("%lldms %d %s\n", now_time() - philo->start_time, philo->id + 1,
			str);
	pthread_mutex_unlock(philo->print);
}
