/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/06 23:01:55 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(unsigned long	time)
{
	unsigned long	temporizator;

	temporizator = get_time();
	while (temporizator + time > get_time())
		usleep(250);
}
//my_sleep(1) == usleep(1000);

void	print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->lock_print);
	printf("%lu %i %s\n", get_time() - philo->info->start_time ,philo->id, str);
	pthread_mutex_unlock(&philo->info->lock_print);

}
int	one_verification(t_philo *philo)
{
	if (philo->info->n_philo > 1)
		return (0);
	print_philo(philo, "has taken a fork");
	my_sleep(philo->info->time_to_die);
	print_philo(philo, "is dead");
	return (1);
}

void	*philo_routine(t_philo *philo)
{
	if (one_verification(philo))
		return (NULL);
	while (!philo->dead)
	{
		pthread_mutex_lock(&philo->info->n_fork[philo->id]);
		if (philo->id == 0)
			pthread_mutex_lock(&philo->info->n_fork[philo->info->n_philo - 1]);
		else
			pthread_mutex_lock(&philo->info->n_fork[philo->id - 1]);
		print_philo(philo, "has taken a fork");
		print_philo(philo, "is eating");
		my_sleep(philo->info->time_to_eat);
		pthread_mutex_unlock(&philo->info->n_fork[philo->id]);
		if (philo->id == 0)
			pthread_mutex_unlock(&philo->info->n_fork[philo->info->n_philo - 1]);
		else
			pthread_mutex_unlock(&philo->info->n_fork[philo->id - 1]);
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep);
		print_philo(philo, "is thinking");
		philo->dead = 1;
	}
	print_philo(philo, "is dead");
	return (NULL);
}
