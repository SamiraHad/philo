/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamira <hsamira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:45:35 by hsamira           #+#    #+#             */
/*   Updated: 2025/06/23 17:49:32 by hsamira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Ce projet simule des philosophes qui mangent autour d’une table
ronde avec des fourchettes partagées.

Chaque philosophe est un thread qui répète sans cesse ces actions :
 manger,dormir, penser.

Pour manger,il faut prendre 2 fourchettes (des mutex) :
 celle de gauche et celle de droite.

 Les fourchettes sont partagées entre les philosophes voisins,
	donc ils doivent attendre leur tour.

Il y a aussi des mutex globaux pour protéger l’accès aux ressources partagées
 (écriture,état des philosophes).

Un thread "observateur/monitor" surveille si un philosophe meurt
(trop longtemps sans manger).

Si un philosophe meurt, la simulation s’arrête.

Sinon, les philosophes continuent leurs actions en boucle.*/

#include "philo.h"

int	check_arg_is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_if_args_are_valid(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_arg_is_number(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_is_number(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_is_number(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_is_number(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || check_arg_is_number(argv[5]) == 1))
		return (write(2, "Invalid value for num_times_to_eat\n", 35), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
	{
		write(2, "Nombre d'arguments incorrect\n", 29);
		return (1);
	}
	if (check_if_args_are_valid(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
