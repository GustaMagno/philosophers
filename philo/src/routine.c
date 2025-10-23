/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/23 20:59:40 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void	*monitor_philos(t_info *info)
{
	int	i;
	
	i = 0;
	while (1)
	{
		if (i == info->n_philo)
			i = 0;
		pthread_mutex_lock(&info->philo[i].mutex_eat);
		if (get_time() >= info->philo[i].eating)
		{
			set_dead(info, i);
			pthread_mutex_unlock(&info->philo[i].mutex_eat);
			break;
		}
		pthread_mutex_unlock(&info->philo[i].mutex_eat);
		usleep(1);
		i++;
	}
	return (info);
}

void	fork_philo(t_philo *philo,  pthread_mutex_t *fork)
{
	// pthread_mutex_lock(&philo->info->is_dead);
	// // if (philo->info->dead && fork)
	// // {
	// // 	pthread_mutex_unlock(&philo->info->is_dead);
	// // 	return ;
	// // }
	// pthread_mutex_unlock(&philo->info->is_dead);
	if (fork)
	{
		pthread_mutex_lock(fork);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_unlock(philo->first);
		pthread_mutex_unlock(philo->second);
	}
}

int	one_verification(t_philo *philo)
{
	if (philo->info->n_philo > 1)
		return (0);
	print_philo(philo, "has taken a fork");
	my_sleep(philo->info->time_to_die, 0);
	print_philo(philo, "is dead");
	return (1);
}

void	*philo_routine(t_philo *philo)
{
	if (one_verification(philo))
		return (NULL);
	if (!(philo->info->n_philo % 2) && philo->id % 2 == 0)
	{
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep, philo->info);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->info->is_dead);
		if (philo->info->dead)
			return(pthread_mutex_unlock(&philo->info->is_dead), NULL);
		pthread_mutex_unlock(&philo->info->is_dead);
		fork_philo(philo, philo->first);
		fork_philo(philo, philo->second);
		print_philo(philo, "is eating");
		my_sleep(philo->info->time_to_eat, philo->info);
		fork_philo(philo,  NULL);
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep, philo->info);
		print_philo(philo, "is thinking");
	}
	return (NULL);
}
