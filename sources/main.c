/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:36:52 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/15 15:12:26 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;
	t_forks	*forks;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong number or arguments"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	philo = malloc(sizeof(t_philo) * 201);
	if (!philo)
	{
		free(data);
		return (1);
	}
	forks = malloc(sizeof(t_forks) * 201);
	if (!forks)
	{
		free(data);
		free(philo);
		return (1);
	}
	if (main_placeholder(data, philo, forks, argv) == 1)
		return (1);
	return (0);
}

int	main_placeholder(t_data *d, t_philo *p, t_forks *f, char **argv)
{
	int	error_checker;

	error_checker = init_game(d, p, f, argv);
	if (error_checker == 1 || error_checker == 2)
	{
		free_all(d, p, f);
		write_error("Error");
		return (1);
	}
	start_game(d, p, f);
	free_all(d, p, f);
	return (0);
}
