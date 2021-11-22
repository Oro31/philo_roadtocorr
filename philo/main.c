/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:21:38 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/22 08:33:04 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_exit(t_philo **philos, t_vars *vars, int code)
{
	int	i;

	if (code == 0)
	{
		printf("Error\n");
		return (0);
	}
	vars->ret = pthread_mutex_destroy(&vars->write);
	if (code == 1)
		printf("Error : failed initialising mutex\n");
	else
	{
		i = -1;
		while (++i < vars->nb_philos)
			vars->ret = pthread_mutex_destroy(&vars->forks[i].mutex);
		if (code == 2)
			printf("Error : failed creating philos thread\n");
		else if (code == 3)
			printf("Error : failed joining thread\n");
	}
	free(vars->forks);
	free(philos[0]);
	return (0);
}

static int	ft_handle_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_is_int(argv[i]))
		{
			printf("Error : wrong arguments\n");
			return (0);
		}
	}
	return (1);
}

int	ft_set_vars(t_vars *vars)
{
	if (pthread_mutex_init(&vars->write, NULL))
		return (0);
	vars->play = 1;
	return (ft_init_forks(vars));
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;

	philos = NULL;
	if (!ft_handle_argv(argc, argv))
		return (0);
	if (!ft_init_vars(&vars, &philos, argc, argv))
		return (ft_exit(&philos, &vars, 0));
	if (!ft_set_vars(&vars))
		return (ft_exit(&philos, &vars, 1));
	if (gettimeofday(&vars.initial_tmstmp, NULL))
		return (ft_exit(&philos, &vars, 4));
	if (!ft_create_philo_th(&vars, &philos))
		return (ft_exit(&philos, &vars, 2));
	i = -1;
	while (++i < vars.nb_philos)
		if (pthread_join(philos[i].th_philo, NULL))
			return (ft_exit(&philos, &vars, 3));
	if (pthread_join(vars.th_vars, NULL))
		return (ft_exit(&philos, &vars, 3));
	return (ft_exit(&philos, &vars, 4));
}
