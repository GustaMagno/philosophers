/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:09 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/10 21:12:51 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int argc, char **argv, t_info *info);


void	assign_philo(t_info *info)
{
	int				i;

	i = 0;
	while(i < info->n_philo)
	{
		pthread_mutex_init(&info->n_fork[i], NULL);
		info->philo[i].id = i + 1;
		info->philo[i].info = info;
		info->philo[i].dead = 0;
		i++;
	}
	info->start_time = get_time();
	pthread_mutex_init(&info->lock_print, NULL);
}

int main(int argc, char **argv)
{
	static t_info	info;
	int				i;

	i = 0;
	if (!parsing(argc, argv, &info))
		return (write(2, "Error\n", 6), 0);
	assign_philo(&info);
	while (i < info.n_philo)
	{
		pthread_create(&info.philo[i].thread, NULL, (void *)conditions_philo, &info.philo[i]);
		i++;
	}
	i = 0;
	while (i < info.n_philo)
	{
		pthread_join(info.philo[i].thread, NULL);
		i++;
	}
	free(info.n_fork);
	free(info.philo);
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);

int pthread_detach(pthread_t thread);

int pthread_join(pthread_t thread, void **retval);

// Mutex (Mutual Exclusion)
int pthread_mutex_init(pthread_mutex_t *mutex,
                       const pthread_mutexattr_t *attr);

int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutex_lock(pthread_mutex_t *mutex);

int pthread_mutex_unlock(pthread_mutex_t *mutex);