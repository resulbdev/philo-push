/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozdemi <rbozdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:40:31 by rbozdemi          #+#    #+#             */
/*   Updated: 2023/03/03 14:40:32 by rbozdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				philo_count;
	int				must_eat;
	int				eat_time;
	int				sleep_time;
	int				die_time;
	int				eat_count;
	int				*is_dead;
	long long int	last_eat;
	long long int	start_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print;
}					t_philo;

int					check_arg(int argc, char **argv);
int					string_to_int(char *str);
long long int		now_time(void);
void				ft_usleep(long long int time);
void				check_dead(t_philo *philo);
void				*routine(void *arg);
void				ft_print(t_philo *philo, char *str);
int					philo_eat_and_sleep(t_philo *philo);
void				*routine(void *arg);
int					check_null(int argc, char **argv);

#endif