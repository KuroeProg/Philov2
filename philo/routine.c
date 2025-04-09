#include "philo.h"

void	think(t_philo *philo)
{
	printstatut(philo, "is thinking");
}

void	p_sleep(t_philo *philo)
{
	printstatut(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!philo->data->simulation)
	{
		think(philo);
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
		{
			put_forks(philo);
			break ;
		}
		put_forks(philo);
		p_sleep(philo);
	}
	// put_forks(philo);
	return (NULL);
}
