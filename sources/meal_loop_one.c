/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_loop_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:47:23 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/14 13:52:47 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*meal_loop_do_one(void *void_philosopher)
{
	t_philo			*philo;

	philo = (t_philo *)void_philosopher;
	printing_status(philo->data, philo->id, "is thinking", 3);
	smart_sleep(philo->data->tdie);
	pthread_mutex_lock(&(philo->data->finishing_diner));
	philo->data->died = 1;
	pthread_mutex_unlock(&(philo->data->finishing_diner));
	printing_status(philo->data, philo->id, "died", 4);
	return (NULL);
}
