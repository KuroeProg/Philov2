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
static int    is(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->sim_mutex);
    if (philo->data->simulation)
    {
        pthread_mutex_unlock(&philo->data->sim_mutex);
        return 1;
    }
    pthread_mutex_unlock(&philo->data->sim_mutex);
    return 0;
}
void	*routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat / 2);
    while (1)
    {
        if (is(philo))
            break ;
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
    return (NULL);
}
