/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:12:30 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/19 15:14:17 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

/*
Explication :
transforme un const char * en un int en commencant par trim les char inutiles,
checkant le signe, puis en iterant sur la chaine de charactere
*/

int	checkdigit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	number;

	i = 0;
	neg = 1;
	number = 0;
	if (checkdigit(nptr))
		return (-1);
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -neg;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] -48);
		i++;
	}
	return (number * neg);
}
