/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:45:51 by hsamira           #+#    #+#             */
/*   Updated: 2025/07/05 17:08:55 by hsamira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			dernier_repas;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				*dead;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;
typedef struct s_program
{
	int				is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

// philo.c
int					check_arg_is_number(char *arg);
int					check_if_args_are_valid(char **argv);
void				destroy_all(char *str, t_program *program,
						pthread_mutex_t *forks_array);

// init.c
void				init_program(t_program *program, t_philo *philos);
void				init_forks(pthread_mutex_t *forks_array, int philo_num);
void				init_philos(t_philo *philos, t_program *program,
						pthread_mutex_t *forks_array, char **argv);
void				init_philo_params(t_philo *philo, char **argv);

// threads.c
int					thread_create(t_program *program,
						pthread_mutex_t *forks_array);
void				*monitor_philosophers_status(void *pointer);
void				*philo_routine(void *pointer);

// routine.c
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

// monitor.c
int					dead_loop(t_philo *philo);
int					check_if_all_philosophers_have_eaten(t_philo *philos);
int					check_if_any_philosopher_is_dead(t_philo *philos);
int					check_if_philo_is_dead(t_philo *philo, size_t time_to_die);

// utils.c
int					ft_atoi(char *str);
int					ft_usleep_ms(size_t microseconds);
int					ft_strlen(char *str);
void				print_philo_message(char *str, t_philo *philo, int id);
size_t				get_current_time_ms(void);

#endif
