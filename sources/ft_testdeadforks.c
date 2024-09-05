/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_testdeadforks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:13:57 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/19 15:16:51 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	testdeadforks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->finishing_diner));
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		return (1);
	}
	if ((philo->data->teat
			- philo->data->tsleep) + (timestamp()
			- philo->time_last_meal)
		> philo->data->tdie + 1)
	{
		philo->data->died = 1;
		smart_sleep(philo->data->tdie - (timestamp() - philo->time_last_meal));
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		printing_status(philo->data, philo->id, "died", 4);
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->finishing_diner));
	return (0);
}

int	testdeadforks2(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->finishing_diner));
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		return (1);
	}
	if ((timestamp() - philo->time_last_meal)
		+ philo->data->tsleep > philo->data->tdie)
	{
		philo->data->died = 1;
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		printing_status(philo->data, philo->id, "is sleeping", 2);
		pthread_mutex_lock(&(philo->data->finishing_diner));
		smart_sleep(philo->data->tdie
			- (timestamp() - philo->time_last_meal));
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		printing_status(philo->data, philo->id, "died", 4);
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->finishing_diner));
	return (0);
}

int	check_sleep_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->finishing_diner));
	if (!(philo->data->died) && philo->data->tsleep > philo->data->tdie)
	{
		philo->data->died = 1;
		printing_status(philo->data, philo->id, "is sleeping", 2);
		smart_sleep(philo->data->tdie);
		printing_status(philo->data, philo->id, "died", 4);
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		return (1);
	}
	if (philo->data->died)
	{
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->finishing_diner));
	return (0);
}

int	testdeadforks3(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->finishing_diner));
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		return (1);
	}
	if (timestamp() - philo->time_last_meal > philo->data->tdie)
	{
		philo->data->died = 1;
		smart_sleep(philo->data->tdie - (timestamp() - philo->time_last_meal));
		pthread_mutex_unlock(&(philo->data->finishing_diner));
		printing_status(philo->data, philo->id, "died", 4);
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->finishing_diner));
	return (0);
}
