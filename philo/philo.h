/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiachet <cfiachet@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:10:30 by cfiachet          #+#    #+#             */
/*   Updated: 2025/04/11 12:21:20 by cfiachet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data
{
	struct timeval	start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	sim_mutex;
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_to_eat;
	int				simulation;
	struct s_philo	*philos;
	int				check;
}				t_data;

typedef struct s_philo
{
	int				id;
	struct timeval	start_time;
	long int		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	int				meals_eaten;
	int				is_full;
}				t_philo;

/*init functions*/
int			init_value(char **av, t_data *data);
int			start_init_philo(t_data *data, t_philo **philo);
int			init_philo(t_data *data, t_philo *philo);
int			init_mutex(t_data *data, t_philo *philo);
int			fork_to_philo(t_data *data, t_philo **philo);

/*print*/
void		printstatut(t_philo *philo, char *status);

/*monitoring*/

int			check_meals(t_philo *philo, t_data *data);
int			monitoring(t_data *data, t_philo *philo);
void		*check_death(void *arg);

/*routine*/
void		*routine(void *arg);
void		think(t_philo *philo);

/*utils*/
long		ft_atol(const char *str);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
void		cleanup(t_data *data, t_philo *philo);
void		cleanup_mutexes(t_data *data, t_philo *philo);

/* forks*/
int			take_forks(t_philo *philo);
int			eat(t_philo *philo);
void		put_forks(t_philo *philo);

/*parsing*/
void		parsing(char **av);

#endif