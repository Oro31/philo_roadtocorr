/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:59:42 by rvalton           #+#    #+#             */
/*   Updated: 2021/12/07 10:41:16 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_taken_a_fork(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->vars->write);
	ft_dead(philo);
	if (philo->alive)
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("has taken a fork", ft_timediff(philo->i_ttmp, philo->t),
			(i + 1));
	}
	pthread_mutex_unlock(&philo->vars->write);
}

void	ft_sleeping(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->vars->write);
	ft_dead(philo);
	if (philo->alive)
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("is sleeping", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
	}
	pthread_mutex_unlock(&philo->vars->write);
}

void	ft_eating(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->vars->write);
	ft_dead(philo);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->ret = gettimeofday(&philo->last_meal, NULL);
		ft_printf("is eating", ft_timediff(philo->i_ttmp, philo->last_meal),
			(i + 1));
		pthread_mutex_unlock(&philo->last_meal_mutex);
	}
	pthread_mutex_unlock(&philo->vars->write);
}

void	ft_thinking(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->vars->write);
	ft_dead(philo);
	if (philo->alive)
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("is thinking", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
	}
	pthread_mutex_unlock(&philo->vars->write);
}

void	ft_died(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->vars->write);
	ft_dead(philo);
	if (philo->alive)
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_printf("died", ft_timediff(philo->i_ttmp, philo->t), (i + 1));
		philo->alive = 0;
		philo->vars->play = 0;
	}
	pthread_mutex_unlock(&philo->vars->write);
}
