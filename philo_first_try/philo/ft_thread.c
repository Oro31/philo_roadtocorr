/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:08:17 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/08 10:34:49 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_is_philo_dead(struct timeval last_meal, t_philo *philo)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (0);
	if (ft_timediff(last_meal, t) > philo->ttd)
		return (1);
	return (0);
}

void	ft_philo_eat(t_philo *philo, int i)
{
	ft_lock_forks_mutex(philo, i);
	if (philo->alive)
	{
		ft_eating(philo, i);
		if (philo->alive)
		{
			if (philo->is_must_eat)
			{
				pthread_mutex_lock(&philo->vars->write);
				ft_satiated(philo);
				pthread_mutex_unlock(&philo->vars->write);
			}
			if (philo->alive)
				ft_usleep(philo->tte, philo);
		}
	}
}

void	ft_philo_sleep(t_philo *philo, int i)
{
	if (philo->alive)
	{
		philo->eating = 0;
		ft_sleeping(philo, i);
		ft_unlock_forks_mutex(philo, i);
		if (philo->alive)
			ft_usleep(philo->tts, philo);
		if (philo->alive)
			ft_thinking(philo, i);
	}
	else if (philo->eating)
		ft_unlock_forks_mutex(philo, i);
}

void	ft_play_philo(t_philo *philo, int i)
{
	if (ft_is_philo_dead(philo->last_meal, philo))
		ft_died(philo, i);
	else if (philo->vars->nb_philos > 1 && philo->alive)
	{
		ft_philo_eat(philo, i);
		ft_philo_sleep(philo, i);
		if (philo->vars->nb_philos % 2 != 0)
			usleep(ft_ttw_before_trying_to_eat(philo));
	}
}

void	*ft_th_philo(void *p_data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p_data;
	i = philo->id;
	if (philo->id % 2 == 1)
		usleep(100);
	philo->ret = gettimeofday(&philo->last_meal, NULL);
	philo->alive = 1;
	ft_thinking(philo, i);
	while (philo->alive)
		ft_play_philo(philo, i);
	return (NULL);
}
