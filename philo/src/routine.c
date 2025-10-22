/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:27:20 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/22 02:31:58 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	*get_now_time(t_info *info)
{
	int	i;
	unsigned long	*save_time;

	i = 0;
	save_time = malloc(info->n_philo * sizeof(unsigned long));
	while (i < info->n_philo)
		save_time[i++] = get_time();
	return (save_time);
}

void	*monitor_philos(t_info *info)
{
	int				i;
	unsigned long	*save_time;
	
	i = 0;
	save_time = get_now_time(info);
	while (1)
	{
		if (i == info->n_philo)
			i = 0;
		if (info->philo[i].eating)
		{
			save_time[i] = get_time();
			info->philo[i].eating = 0;
		}
		if (save_time[i] + info->time_to_die < get_time())
		{
			print_philo(&info->philo[i], "is dead");
			info->dead = 1;
			break ;
		}
		i++;
	}
	free(save_time);
	return (NULL);
}

void	fork_philo(t_philo *philo,  pthread_mutex_t *fork)
{
	if (philo->info->dead && fork)
		return ;
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
	// if (philo->id % 2 == 0)
	// {
	// 	print_philo(philo,  "is sleeping");
	// 	my_sleep(philo->info->time_to_sleep);
	// }
	while (philo->info->dead != 1)
	{
		fork_philo(philo, philo->first);
		fork_philo(philo, philo->second);
		print_philo(philo, "is eating");
		my_sleep(philo->info->time_to_eat, philo->info->dead);
		fork_philo(philo,  NULL);
		print_philo(philo,  "is sleeping");
		my_sleep(philo->info->time_to_sleep, philo->info->dead);
		print_philo(philo, "is thinking");
	}
	return (NULL);
}
