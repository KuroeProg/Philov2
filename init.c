#include "philo.h"

int	init_value(char **av, t_data *data)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	data->num_philo = ft_atol(av[1]);
	pthread_mutex_init(&data->sim_mutex, NULL);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5] && *av[5])
		data->num_to_eat = ft_atol(av[5]);
	else
		data->num_to_eat = 0;
	if (data->num_philo < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (0);
	if (data->num_to_eat < 0)
		return (0);
	data->start_time = now;
	data->simulation = 0;
	return (1);
}

int	start_init_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!*philo)
		return (0);
	while (i < data->num_philo)
	{
		(*philo)[i].id = i + 1;
		if (!init_philo(data, &(*philo)[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_philo(t_data *data, t_philo *philo)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	// philo->id = 0;
	philo->start_time = data->start_time;
	philo->last_meal = now;
	philo->left_fork = NULL;
	philo->right_fork = NULL;
	philo->data = data;
	philo->thread = 0;
	if (pthread_mutex_init(&philo->meal_mutex, NULL))
	{
		write(2, "Mutex initialization failed\n", 29);
		return (0);
	}
	philo->meals_eaten = 0;
	philo->is_full = 0;
	return (1);
}

int	init_mutex(t_data *data, t_philo *philo)
{
	int	i;

	(void)philo;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->fork)
		return (0);
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	fork_to_philo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		(*philo)[i].left_fork = &data->fork[i];
		(*philo)[i].right_fork = &data->fork[(i + 1) % data->num_philo];
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&(*philo)[i].thread, NULL, routine, &(*philo)[i]))
			return (0);
		i++;	
	}
	return (1);
}