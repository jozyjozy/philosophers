/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:26:12 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/01 14:41:10 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	init_philo(t_data	*data, t_philo	*philo, t_forks	*forks)
{
	int	i;

	i = 1;
	(void)forks;
	while (i <= data->nb_philo)
	{
		philo[i - 1].id = i;
		philo[i - 1].nb_meals = 0;
		philo[i - 1].left_fork_id = i;
		philo[i - 1].right_fork_id = (i + 1) % data->nb_philo;
		if (philo[i - 1].right_fork_id == 0)
			philo[i - 1].right_fork_id = data->nb_philo;
		philo[i - 1].time_last_meal = 0;
		philo[i - 1].forks = forks;
		philo[i - 1].data = data;
		if (pthread_mutex_init(&(philo[i - 1].philo_lvl), NULL))
			return (1);
		i++;
	}
	philo[i - 1].id = -1;
	return (0);
}

int	init_mutex(t_data	*data)
{
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(data->finishing_diner), NULL))
		return (1);
	return (0);
}

int	init_forks(t_data	*data, t_forks	*forks)
{
	int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(forks[i].fork), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_game(t_data	*data, t_philo	*phil, t_forks	*fork, char	**argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->tdie = ft_atoi(argv[2]);
	data->teat = ft_atoi(argv[3]);
	data->tsleep = ft_atoi(argv[4]);
	data->all_ate = 0;
	data->died = 0;
	if (argv[5])
		data->nb_meal_goal = ft_atoi(argv[5]);
	else
		data->nb_meal_goal = -1;
	if (data->nb_meal_goal <= 0 && argv[5])
		return (1);
	if (data->nb_philo < 1 || data->tdie < 0 || data->teat < 0
		|| data->tsleep < 0 || data->nb_philo > 200)
		return (1);
	if (init_forks(data, fork))
		return (2);
	if (init_philo(data, phil, fork))
		return (2);
	if (init_mutex(data))
		return (2);
	return (0);
}
