/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:09 by gustoliv          #+#    #+#             */
/*   Updated: 2025/09/29 21:50:30 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int argc, char **argv)
{
	if (!parsing(argc, argv))
		return (write(2, "Error\n", 6), 0);
}



// Criação e controle de threads
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine)(void *), void *arg);


int pthread_join(pthread_t thread, void **retval);



// Mutex (Mutual Exclusion)
int pthread_mutex_init(pthread_mutex_t *mutex,
		const pthread_mutexattr_t *attr);
		

int pthread_mutex_lock(pthread_mutex_t *mutex);

int pthread_mutex_unlock(pthread_mutex_t *mutex);


int pthread_mutex_destroy(pthread_mutex_t *mutex);