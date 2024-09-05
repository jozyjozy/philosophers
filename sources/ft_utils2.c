/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:09:49 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/19 13:56:19 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_finish(t_data	*data, t_philo	*philo)
{
	(void) philo;
	pthread_mutex_lock(&(data->finishing_diner));
	if (data->all_ate == data->nb_philo)
	{
		pthread_mutex_unlock(&(data->finishing_diner));
		return (1);
	}
	pthread_mutex_unlock(&(data->finishing_diner));
	return (0);
}

int	death_checker2(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo && philo[i].id != -1)
	{
		pthread_mutex_lock(&(philo[i].philo_lvl));
		if (time_diff(philo[i].time_last_meal, timestamp()) > data->tdie)
		{
			data->died = 1;
			printing_status(data, philo[i].id, "died", 4);
			pthread_mutex_unlock(&(philo[i].philo_lvl));
			return (1);
		}
		pthread_mutex_unlock(&(philo[i].philo_lvl));
		i++;
	}
	return (-1);
}

void	printing_status2(t_data *data, int p_id, t_philo	*p)
{
	pthread_mutex_lock(&(data->writing));
	print_death(p_id, p->time_last_meal + data->tdie - data->time);
	pthread_mutex_unlock(&(data->writing));
}

void	free_all(t_data	*data, t_philo	*philo, t_forks	*forks)
{
	free(forks);
	free(philo);
	free(data);
}

void	ft_lock_forks(int i, t_philo	*philo)
{
	if (i == 1)
	{
		if (philo->id % 2)
		{
			pthread_mutex_lock(&(philo->forks[philo->right_fork_id - 1].fork));
			pthread_mutex_lock(&(philo->forks[philo->left_fork_id - 1].fork));
		}
		else
		{
			pthread_mutex_lock(&(philo->forks[philo->left_fork_id - 1].fork));
			pthread_mutex_lock(&(philo->forks[philo->right_fork_id - 1].fork));
		}
	}
	else if (i == 0)
	{
		pthread_mutex_unlock(&(philo->forks[philo->left_fork_id - 1].fork));
		pthread_mutex_unlock(&(philo->forks[philo->right_fork_id - 1].fork));
	}
}
