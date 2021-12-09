/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 06:52:44 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/08 10:33:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_printf(char *msg, long tmstmp, int i)
{
	printf("%ld %d %s\n", tmstmp / 1000, i, msg);
}

void	ft_kill(t_philo *philo, int i)
{
	struct timeval	t;

	pthread_mutex_lock(&philo->vars->write);
	if (philo->vars->play)
	{
		if (gettimeofday(&t, NULL))
			return ;
		ft_printf("died", ft_timediff(philo->i_ttmp, t), (i + 1));
		philo->vars->play = 0;
	}
	pthread_mutex_unlock(&philo->vars->write);
}

void	*ft_th_monitoring(void *p_data)
{
	t_philo	**philos;
	int		i;
	int		nb_philos;
	int		play;

	philos = (t_philo **)p_data;
	play = 1;
	nb_philos = philos[0][0].vars->nb_philos;
	while (play)
	{
		usleep(2500);
		i = -1;
		while (++i < nb_philos)
		{
			pthread_mutex_lock(&philos[0][i].last_meal_mutex);
			if (ft_is_philo_dead(philos[0][i].last_meal, &philos[0][i]))
			{
				ft_kill(&philos[0][i], i);
				play = 0;
			}
			pthread_mutex_unlock(&philos[0][i].last_meal_mutex);
		}
	}
	return (NULL);
}
