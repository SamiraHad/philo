/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:54:15 by hsamira           #+#    #+#             */
/*   Updated: 2025/08/12 18:50:57 by hsamira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	print_philo_message("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_message("is sleeping", philo, philo->id);
	ft_usleep_ms(philo->time_to_sleep);
}

static int	take_forks(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	print_philo_message("has taken a fork", philo, philo->id);
	if (philo->number_of_philosophers == 1)
	{
		if (philo->fork_left < philo->fork_right)
			pthread_mutex_unlock(philo->fork_left);
		else
			pthread_mutex_unlock(philo->fork_right);
		ft_usleep_ms(philo->time_to_die);
		return (1);
	}
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	print_philo_message("has taken a fork", philo, philo->id);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo))
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->dernier_repas = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_philo_message("is eating", philo, philo->id);
	if (ft_usleep_ms(philo->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

/*void	philo_eat(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	print_philo_message("has taken a fork", philo, philo->id);
	if (philo->number_of_philosophers == 1)
	{
		if (philo->fork_left < philo->fork_right)
			pthread_mutex_unlock(philo->fork_left);
		else
			pthread_mutex_unlock(philo->fork_right);
		ft_usleep_ms(philo->time_to_die);
		return ;
	}
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	print_philo_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->dernier_repas = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_philo_message("is eating", philo, philo->id);
	if (ft_usleep_ms(philo->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}*/