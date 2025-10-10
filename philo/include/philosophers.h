/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:22:32 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/10 20:45:13 by gustoliv         ###   ########.fr       */
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

typedef struct s_info t_info;

typedef struct s_philo
{
	int			id;
	int			fork;
	int			dead;
	size_t		time_to_die;
	pthread_t	thread;
	t_info 		*info;
}	t_philo;
struct s_info
{
	int				n_philo;
	size_t			time_to_eat;
	size_t			start_time;
	size_t			optional_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	pthread_mutex_t *n_fork;
	pthread_mutex_t lock_print;
	t_philo 		*philo;
};

void			*conditions_philo(t_philo *philo);
void			print_philo(t_philo *philo, char *str);
void			my_sleep(unsigned long	time);
unsigned long	get_time(void);

#endif