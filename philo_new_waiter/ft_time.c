/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:06:21 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/19 09:34:32 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_timediff(struct timeval t0, struct timeval t1)
{
	return ((t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec));
}

void	ft_usleep(long ttw, t_philo *philo)
{
	struct timeval	t;
	struct timeval	start;
	int				ret;

	ret = gettimeofday(&t, NULL);
	ret = gettimeofday(&start, NULL);
	while (ft_timediff(start, t) < ttw
		&& !ft_is_philo_dead(philo->last_meal, philo))
	{
		usleep(500);
		ret = gettimeofday(&t, NULL);
	}
	if (ft_is_philo_dead(philo->last_meal, philo))
		ft_died(philo, philo->id);
}

long	ft_ttw_before_trying_to_eat(t_philo *philo)
{
	long	res;

	if (philo->vars->nb_philos % 2 == 0)
		res = 1000;
	else
	{
		res = philo->ttd - (philo->tte + philo->tts);
		res = res / 2;
	}
	return (res);
}
