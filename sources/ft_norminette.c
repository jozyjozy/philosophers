/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norminette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:31:49 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/15 13:00:37 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	meal_loop_norminette2(t_philo	*philo, t_data	*data)
{
	if (!((philo->id % 2) == 0) && philo->id == data->nb_philo
		&& (data->tdie <= 3 * data->teat))
	{
		printing_status(data, philo->id, "is thinking", 3);
		smart_sleep(data->tdie);
		testdeadforks(philo);
	}
	else if (!((philo->id % 2) == 0))
	{
		printing_status(data, philo->id, "is thinking", 3);
		if (data->tdie >= data->teat)
			smart_sleep(philo->data->teat);
		else
			smart_sleep(philo->data->tdie);
		testdeadforks(philo);
	}
}

int	meal_loop_norminette(t_philo	*philo, t_data	*data)
{
	if (philo->nb_meals == philo->data->nb_meal_goal)
		data->all_ate++;
	if (check_finish(data, philo) == 1)
		return (1);
	else if (death_checker(data, philo) == 1)
		return (1);
	else
		philo_eats(philo);
	if (check_finish(data, philo) == 1)
		return (1);
	if (death_checker(data, philo) == 1)
		return (1);
	else
	{
		pthread_mutex_lock(&(philo->philo_lvl));
		printing_status(data, philo->id, "is thinking", 3);
		if (testdeadforks(philo) == 1)
		{
			pthread_mutex_unlock(&(philo->philo_lvl));
			return (1);
		}
		pthread_mutex_unlock(&(philo->philo_lvl));
		smart_sleep(data->teat - data->tsleep);
	}
	return (0);
}

int	philo_eats_norminette(t_philo	*philo, t_data	*data)
{
	printing_status(data, philo->id, "has taken a fork", 0);
	philo->time_last_meal = timestamp();
	smart_sleep(data->teat);
	(philo->nb_meals)++;
	pthread_mutex_lock(&(philo->philo_lvl));
	ft_lock_forks(0, philo);
	pthread_mutex_unlock(&(philo->philo_lvl));
	if (death_checker(data, philo) == 1)
		return (1);
	if (testdeadforks2(philo) == 1)
		return (1);
	if (check_sleep_death(philo) == 1)
		return (1);
	return (0);
}

int	start_game_norminette(t_philo *philo, int i, int j)
{
	if (pthread_create(&(philo[i].thread_id), NULL, meal_loop, (&philo[i])))
	{
		while (j != i)
		{
			pthread_join(philo[j].thread_id, NULL);
			j++;
		}
		return (1);
	}
	return (0);
}
