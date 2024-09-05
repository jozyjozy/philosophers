/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:31:11 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/19 15:15:31 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	philo_eats(t_philo *philo)
{
	t_data	*data;

	pthread_mutex_lock(&(philo->philo_lvl));
	data = philo->data;
	pthread_mutex_unlock(&(philo->philo_lvl));
	ft_lock_forks(1, philo);
	if (philo_eats_norminette(philo, data) == 1)
		return ;
	if (check_finish(data, philo) == 1)
		return ;
	pthread_mutex_lock(&(philo->philo_lvl));
	printing_status(data, philo->id, "is sleeping", 2);
	smart_sleep(data->tsleep);
	pthread_mutex_unlock(&(philo->philo_lvl));
}

void	*meal_loop(void *void_philosopher)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)void_philosopher;
	pthread_mutex_lock(&(philo->philo_lvl));
	data = philo->data;
	meal_loop_norminette2(philo, data);
	pthread_mutex_unlock(&(philo->philo_lvl));
	while ((pthread_mutex_lock(&(data->finishing_diner)) || 1)
		&& !(data->died)
		&& (pthread_mutex_unlock(&(data->finishing_diner)) || 1))
	{
		if (meal_loop_norminette(philo, data) == 1)
			return (NULL);
	}
	pthread_mutex_unlock(&(data->finishing_diner));
	return (NULL);
}

void	exit_launcher(t_data *data, t_philo *philos, t_forks	*forks)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(philos[i].philo_lvl));
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(forks[i].fork));
	pthread_mutex_destroy(&(data->meal_check));
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->finishing_diner));
}

int	death_checker(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->finishing_diner));
	if (data->died == 1)
	{
		pthread_mutex_unlock(&(data->finishing_diner));
		return (1);
	}
	pthread_mutex_unlock(&(data->finishing_diner));
	pthread_mutex_lock(&(philo->philo_lvl));
	if (time_diff(philo->time_last_meal, timestamp()) > data->tdie)
	{
		pthread_mutex_unlock(&(philo->philo_lvl));
		pthread_mutex_lock(&(data->finishing_diner));
		data->died = 1;
		pthread_mutex_unlock(&(data->finishing_diner));
		printing_status(data, philo->id, "died", 4);
		return (1);
	}
	pthread_mutex_unlock(&(philo->philo_lvl));
	return (-1);
}

int	start_game(t_data *data, t_philo *philo, t_forks *forks)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	data->time = timestamp();
	while (i < data->nb_philo)
	{
		philo[i].time_last_meal = timestamp();
		if (data->nb_philo == 1)
		{
			if (pthread_create(&(philo[0].thread_id),
					NULL, meal_loop_do_one, (&philo[0])))
				return (1);
			break ;
		}
		if (start_game_norminette(philo, i, j) == 1)
			return (1);
		i++;
	}
	exit_launcher(data, philo, forks);
	return (0);
}
