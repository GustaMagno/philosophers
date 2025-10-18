/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/16 22:01:55 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_philo(t_philo *philo, int lock)
{
	static int	fork_time;

	if (lock)
	{
		if (philo->id % 2 == 1 && !fork_time)
			pthread_mutex_lock(philo->right);
		else if (philo->id % 2 == 0 && !fork_time)
			pthread_mutex_lock(philo->left);
		else if (philo->id % 2 == 1 && fork_time)
			pthread_mutex_lock(philo->left);
		else
			pthread_mutex_lock(philo->right);
		fork_time = 1 - fork_time;
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
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
	if (philo->id % 2 == 0)
	{
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep);
	}
	while (!philo->dead)
	{
		fork_philo(philo, 1);
		fork_philo(philo, 1);
		print_philo(philo, "is eating");
		my_sleep(philo->info->time_to_eat);
		fork_philo(philo, 0);
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep);
		print_philo(philo, "is thinking");
	}
	print_philo(philo, "is dead");
	return (NULL);
}
