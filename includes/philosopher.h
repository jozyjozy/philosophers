/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlarue <jlarue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:02:12 by jlarue            #+#    #+#             */
/*   Updated: 2023/06/15 15:12:05 by jlarue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_forks
{
	pthread_mutex_t		fork;
}	t_forks;

typedef struct s_philo
{
	int					id;
	int					nb_meals;
	int					left_fork_id;
	int					right_fork_id;
	long long			time_last_meal;
	struct s_data		*data;
	struct s_forks		*forks;
	pthread_mutex_t		philo_lvl;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					tdie;
	int					teat;
	int					tsleep;
	int					nb_meal_goal;
	long long			time;
	int					died;
	int					all_ate;
	pthread_mutex_t		finishing_diner;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		writing;
}	t_data;

/*--- main ---*/
int			main_placeholder(t_data *d, t_philo *p, t_forks *f, char **argv);
/*--- initialisation ---*/
int			init_game(t_data	*d, t_philo	*p, t_forks	*f, char	**argv);
/*--- error manager ---*/
int			write_error(char *str);
/*--- game ---*/
void		philo_eats(t_philo *philo);
void		*meal_loop(void *void_philosopher);
void		exit_launcher(t_data *data, t_philo *philos, t_forks	*forks);
int			death_checker(t_data *r, t_philo *philos);
int			start_game(t_data *data, t_philo *philo, t_forks *forks);
/*--- utils ---*/
void		printing_status(t_data *data, int philo_id, char *status, int i);
void		print_death(int philo_id, long long time_of_death);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);
void		smart_sleep(long long time);
/* --- utils2 --- */
int			check_finish(t_data	*data, t_philo	*philo);
void		free_all(t_data	*data, t_philo	*philo, t_forks	*forks);
int			death_checker2(t_data *data, t_philo *philo);
void		printing_status2(t_data *data, int p_id, t_philo	*p);
void		ft_lock_forks(int i, t_philo	*philo);
/*--- libft ---*/
int			ft_atoi(const char *nptr);
/*--- testdeadforks ---*/
int			testdeadforks(t_philo *philo);
int			testdeadforks2(t_philo *philo);
int			testdeadforks3(t_philo *philo);
int			check_sleep_death(t_philo *philo);
/*--- meal_loop_do_one ---*/
void		*meal_loop_do_one(void *void_philosopher);
/*--- norminette ---*/
int			meal_loop_norminette(t_philo	*philo, t_data	*data);
void		meal_loop_norminette2(t_philo	*philo, t_data	*data);
int			philo_eats_norminette(t_philo	*philo, t_data	*data);
int			start_game_norminette(t_philo *philo, int i, int j);
#endif
