/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:37:22 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/10 19:37:23 by gustoliv         ###   ########.fr       */
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