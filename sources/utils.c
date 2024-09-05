/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:45:49 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/14 13:30:51 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"
/*
Explication :
1) On lock le mutex writing comme ca on ne peut passer qu'une fois a la fois
par le code entre la ligne 21 et 42.
2) On Verifie que personne est mort
3) Slon les cas (represente par l'int i) on ecrit un message contenant :
[time de l'action] [philo_id] [status] [petit emoji sympa]
2) On unlock le mutex
*/
void	printing_status(t_data *data, int philo_id, char *status, int i)
{
	pthread_mutex_lock(&(data->finishing_diner));
	if (i != 4 && !data->died)
	{
		printf("%lld ", timestamp() - data->time);
		printf("%d ", philo_id);
		if (i == 0)
		{
			printf("%s\n", status);
			printf("%lld ", timestamp() - data->time);
			printf("%d ", philo_id);
			printf("%s\n", status);
			printf("%lld ", timestamp() - data->time);
			printf("%d ", philo_id);
			printf("is eating\n");
		}
		else if (i == 2)
			printf("%s\n", status);
		else if (i == 3)
			printf("%s\n", status);
	}
	else if (i == 4)
		print_death(philo_id, timestamp() - data->time);
	pthread_mutex_unlock(&(data->finishing_diner));
}

void	print_death(int philo_id, long long time_of_death)
{
	printf("%lld ", time_of_death);
	printf("%d ", philo_id);
	printf("died\n");
}

/*
Explication:
On utilise ici le sys/time.h
1) On doit alors creer une structure de type timeval qui nous permet
d'utiliser gettimeofday() et d'enregistrer ce qui nous interesse
dans la variable ici nomme time
2) Par souci de comprehension on creer trois variables
- secondes qui prend la valeur de time.tv_sec
- microsecondes qui prend la valeur de time.tv_usec
- millisecondes = secondes * 1000 + microsec / 1000
On retourne millisecondes
*/
long long	timestamp(void)
{
	struct timeval	time;
	long long		secondes;
	long long		microsecondes;
	long long		millisecondes;

	gettimeofday(&time, NULL);
	secondes = time.tv_sec;
	microsecondes = time.tv_usec;
	millisecondes = secondes * 1000 + microsecondes / 1000;
	return (millisecondes);
}

/*
Explication:
Renvoie juste la difference entre deux long long qui sont la valeur
en milliseconde du present vs le passe donc en faisant une soustraction
on obtient le temps passe
*/
long long	time_diff(long long past_time, long long present_time)
{
	return (present_time - past_time);
}

/*
Explication
usleep(10) suspend l'exec d'un thread pour au moins 10 milliseconds mdr
donc c'est pas precis
On faut donc boucler de au maximum 10ms par 10ms
une fois que la difference entre le debut de la boucle (i) et
maintenant depasse ou est egale au temps qu'on voulait attendre (time)
alors on break et on fini ce smart_sleep
*/
void	smart_sleep(long long time)
{
	long long	i;

	i = timestamp();
	while (1)
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(10);
	}
}
