/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:09 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/22 02:23:14 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int argc, char **argv, t_info *info);

void	condition_fork(t_info *info, int i)
{
	if (info->philo[i].id == info->n_philo)
	{
		info->philo[i].first = &info->n_fork[0];
		info->philo[i].second = &info->n_fork[i];
		return ;
	}
	if (info->philo[i].id % 2)
	{
		info->philo[i].first = &info->n_fork[i];
		info->philo[i].second = &info->n_fork[i + 1];
		
	}
	else
	{
		info->philo[i].first = &info->n_fork[i + 1];
		info->philo[i].second = &info->n_fork[i];
	}
}

void	assign_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
		pthread_mutex_init(&info->n_fork[i++], NULL);
}

void	assign_philo(t_info *info)
{
	int	i;

	i = 0;
	assign_forks(info);
	while(i < info->n_philo)
	{
		info->philo[i].id = i + 1;
		condition_fork(info, i);
		info->philo[i].info = info;
		info->philo[i++].dead = 0;
	}
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
	info.start_time = get_time();
	while (i < info.n_philo)
	{
		pthread_create(&info.philo[i].thread, NULL, (void *)philo_routine, &info.philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&info.monitor, NULL, (void *)monitor_philos, &info);
	while (i < info.n_philo)
	{
		pthread_join(info.philo[i].thread, NULL);
		i++;
	}
	pthread_join(info.monitor, NULL);
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