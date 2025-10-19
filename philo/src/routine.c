/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/19 20:50:45 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_philo(t_philo *philo,  pthread_mutex_t *fork)
{
	if (fork)
	{
		pthread_mutex_lock(fork);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
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
	// if (philo->id % 2 == 0)
	// {
	// 	print_philo(philo,  "is sleeping");
	// 	my_sleep(philo->info->time_to_sleep);
	// }
	while (!philo->dead)
	{
		fork_philo(philo, philo->left);
		fork_philo(philo, philo->right);
		print_philo(philo, "is eating");
		my_sleep(philo->info->time_to_eat);
		fork_philo(philo,  NULL);
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep);
		print_philo(philo, "is thinking");
	}
	print_philo(philo, "is dead");
	return (NULL);
}
