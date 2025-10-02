/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:24:09 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/02 21:57:02 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int argc, char **argv, t_info *info);

void	create_philo(t_philo *philo, int id)
{
	philo->id = id;
	pthread_create(philo->thread)
}

int main(int argc, char **argv)
{
	static t_info	info;
	int				i;

	i = 0;
	if (!parsing(argc, argv, &info))
		return (write(2, "Error\n", 6), 0);
	while (i < info.n_philo)
	{
		create_philo(&info.philo[i], i + 1);
		i++;
	}
}
