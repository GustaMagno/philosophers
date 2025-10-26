/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:37:22 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/26 22:50:32 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_dead(t_info *info, int i)
{
	pthread_mutex_lock(&info->is_dead);
	info->dead = 1;
	pthread_mutex_unlock(&info->is_dead);
	if (!all_eat(info->philo))
		print_philo(&info->philo[i], "is dead");
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_sleep(unsigned long	time, t_info *info)
{
	unsigned long	temporizator;

	(void)(info);
	temporizator = get_time();
	while (temporizator + time > get_time())
		usleep(10);
}
//my_sleep(1) == usleep(1000);

void	print_philo(t_philo *philo, char *str)
{

	pthread_mutex_lock(&philo->info->is_dead);
	if (philo->info->dead)
	{	
		pthread_mutex_unlock(&philo->info->is_dead);
		return ;
	}
	 	pthread_mutex_unlock(&philo->info->is_dead);
	if (str[3] == 'e')
	{
		pthread_mutex_lock(&philo->mutex_eat);
		philo->eating = get_time() + philo->info->time_to_die + philo->info->time_to_eat;
		philo->eat_times++;
		pthread_mutex_unlock(&philo->mutex_eat);
	}
	pthread_mutex_lock(&philo->info->lock_print);
	printf("%lu %i %s\n", get_time() - philo->info->start_time ,philo->id, str);
	pthread_mutex_unlock(&philo->info->lock_print);
}
