/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: resulbozdemir <resulbozdemir@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:41:07 by rbozdemi          #+#    #+#             */
/*   Updated: 2023/03/06 00:31:21 by resulbozdem      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fill_philo(t_philo *philo, int argc, char **argv)
{
	int	i;
	int	is_dead;

	i = 0;
	is_dead = 0;
	while (i < string_to_int(argv[1]))
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].philo_count = string_to_int(argv[1]);
		philo[i].die_time = string_to_int(argv[2]);
		philo[i].eat_time = string_to_int(argv[3]);
		philo[i].sleep_time = string_to_int(argv[4]);
		if (argc == 6)
			philo[i].must_eat = string_to_int(argv[5]);
		else
			philo[i].must_eat = -1;
		philo[i].last_eat = now_time();
		philo[i].start_time = now_time();
		philo[i].is_dead = &is_dead;
		i++;
	}
}

void	fork_assignment(t_philo *philo, pthread_mutex_t *forks,
		pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->philo_count];
		i++;
	}
	i = 0;
	while (i < philo->philo_count)
	{
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		philo[i].print = print;
		i++;
	}
	pthread_mutex_init(philo->print, NULL);
}

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
		usleep(100);
	}
	while (*philo->is_dead != 1)
	{
		check_dead(philo);
	}
	if (philo->philo_count == 1)
		pthread_join(philo->thread, NULL);
}

void	ft_free(t_philo *philo, pthread_mutex_t *forks, pthread_mutex_t *print)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
	pthread_mutex_destroy(philo->print);
	free(forks);
	free(print);
	free(philo);
}

int	ft_max_int(char **str, int argc)
{
	int			i;
	long int	max;

	i = 1;
	max = 0;
	while (i < argc)
	{
		max = string_to_int(str[i]);
		if (max > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;

	if ((argc != 5 && argc != 6))
	{
		printf("Error: Wrong arguments\n");
		return (0);
	}
	if (!check_arg(argc, argv) || string_to_int(argv[1]) < 1
		|| !check_null(argc, argv) || !ft_max_int(argv, argc))
		return (0);
	philo = malloc(sizeof(t_philo) * string_to_int(argv[1]));
	forks = malloc(sizeof(pthread_mutex_t) * string_to_int(argv[1]));
	print = malloc(sizeof(pthread_mutex_t));
	fill_philo(philo, argc, argv);
	fork_assignment(philo, forks, print);
	create_threads(philo);
	ft_free(philo, forks, print);
	return (0);
}
