/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:22:32 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/02 21:50:15 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef  unsigned int t_usecs;

typedef struct s_philo
{
	int			id;
	int			fork;
	t_usecs		time_to_die;
	pthread_t	thread;
}	t_philo;
typedef struct s_info
{
	int		n_philo;
	t_usecs	time_to_eat;
	t_usecs	optional_eat;
	t_usecs	time_to_die;
	t_usecs	time_to_sleep;
	t_philo *philo;
}	t_info;

#endif