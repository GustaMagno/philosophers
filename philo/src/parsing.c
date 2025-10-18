/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustoliv <gustoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:30:22 by gustoliv          #+#    #+#             */
/*   Updated: 2025/10/05 19:20:46 by gustoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *str)
{
	unsigned int	i;
	int				check;
	long			nb;

	i = 0;
	check = 0;
	nb = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			check++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		i++;
	}
	if (check == 1)
		nb *= -1;
	return (nb);
}

int	check_values(char *argument, int position)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if ((argument[i] < '0' || argument[i] > '9') && argument[i] != 32
		&& argument[i] != 9)
			return (0);
		i++;
	}
	if (position == 1 && ft_atol(argument) < 1)
		return (0);
	else if (position > 1 && ft_atol(argument) < 0)
		return (0);
	return (1);
}

int	parsing(int argc, char **argv, t_info *info)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
		return (0);
	while (argv[i])
	{
		if (!check_values(argv[i], i))
			return (0);
		i++;
	}
	info->n_philo = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		info->optional_eat = ft_atol(argv[5]);
	info->philo = malloc(sizeof(t_philo) * info->n_philo);
	info->n_fork = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	return (1);
}
