/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:28:13 by hsamira           #+#    #+#             */
/*   Updated: 2025/08/16 15:12:58 by hsamira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time_ms() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	check_if_philo_is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time_ms() - philo->dernier_repas > time_to_die
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_any_philosopher_is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].number_of_philosophers)
	{
		if (check_if_philo_is_dead(&philos[i], philos[i].time_to_die))
		{
			print_philo_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_all_philosophers_have_eaten(t_philo *philos)
{
	int	i;
	int	nbr_philos_finished_eating;

	i = 0;
	nbr_philos_finished_eating = 0;
	if (philos[0].number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (i < philos[0].number_of_philosophers)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten
			>= philos[i].number_of_times_each_philosopher_must_eat)
				nbr_philos_finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (nbr_philos_finished_eating == philos[0].number_of_philosophers)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_philosophers_status(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_any_philosopher_is_dead(philos) == 1)
			break ;
		if (check_if_all_philosophers_have_eaten(philos) == 1)
			break ;
		usleep(1000);
	}
	return (pointer);
}
