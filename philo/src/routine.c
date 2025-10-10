/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/10 21:14:55 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_philo(t_philo *philo, int lock)
{
	int	philo_fork;

	philo_fork = philo->id - 1;
	if (lock)
	{
		pthread_mutex_lock(&philo->info->n_fork[philo_fork]);
		print_philo(philo, "has taken a fork");
		if (philo->id == 1)
			pthread_mutex_lock(&philo->info->n_fork[philo->info->n_philo - 1]);
		else
			pthread_mutex_lock(&philo->info->n_fork[philo_fork - 1]);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(&philo->info->n_fork[philo_fork]);
		if (philo->id == 1)
			pthread_mutex_unlock(&philo->info->n_fork[philo->info->n_philo - 1]);
		else
			pthread_mutex_unlock(&philo->info->n_fork[philo_fork - 1]);
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

void	*philo_routine_(t_philo *philo)
{
	if (one_verification(philo))
		return (NULL);
	if (!philo->info->n_philo % 2)
	{
		if (philo->id % 2)
			my_sleep(philo->info->time_to_die);
	}
	while (!philo->dead)
	{
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
