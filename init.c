/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:47:46 by hsamira           #+#    #+#             */
/*   Updated: 2025/08/12 18:46:42 by hsamira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_params(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->number_of_philosophers = ft_atoi(argv[1]);
	if (argv[5])
		philo->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo->number_of_times_each_philosopher_must_eat = -1;
}

static void	assign_forks(t_philo *philo, pthread_mutex_t *forks, int i,
		int nb_philos)
{
	if (i == nb_philos - 1)
	{
		philo->fork_left = &forks[i];
		philo->fork_right = &forks[0];
	}
	else
	{
		philo->fork_left = &forks[i];
		philo->fork_right = &forks[i + 1];
	}
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = ft_atoi(argv[1]);
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_philo_params(&philos[i], argv);
		philos[i].start_time = get_current_time_ms();
		philos[i].dernier_repas = get_current_time_ms();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->is_dead;
		assign_forks(&philos[i], forks, i, nb_philos);
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->is_dead = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
