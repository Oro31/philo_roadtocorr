/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:46 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/19 09:26:28 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_lock_paire(t_philo *philo, int i, int j)
{
	pthread_mutex_lock(&philo->vars->forks[j].mutex);
	if (ft_is_philo_dead(philo->last_meal, philo))
		ft_died(philo, i);
	else
		ft_taken_a_fork(philo, i);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->forks[i].mutex);
		if (ft_is_philo_dead(philo->last_meal, philo))
		{
			ft_died(philo, i);
			pthread_mutex_unlock(&philo->vars->forks[i].mutex);
			pthread_mutex_unlock(&philo->vars->forks[j].mutex);
		}
		else
			ft_taken_a_fork(philo, i);
	}
	else
		pthread_mutex_unlock(&philo->vars->forks[j].mutex);
}

static void	ft_lock_impaire(t_philo *philo, int i, int j)
{
	pthread_mutex_lock(&philo->vars->forks[i].mutex);
	if (ft_is_philo_dead(philo->last_meal, philo))
		ft_died(philo, i);
	else
		ft_taken_a_fork(philo, i);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->vars->forks[j].mutex);
		if (ft_is_philo_dead(philo->last_meal, philo))
		{
			ft_died(philo, i);
			pthread_mutex_unlock(&philo->vars->forks[j].mutex);
			pthread_mutex_unlock(&philo->vars->forks[i].mutex);
		}
		else
			ft_taken_a_fork(philo, i);
	}
	else
		pthread_mutex_unlock(&philo->vars->forks[i].mutex);
}

void	ft_lock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	if (i % 2 == 0)
		ft_lock_paire(philo, i, j);
	else
		ft_lock_impaire(philo, i, j);
}

void	ft_unlock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	pthread_mutex_unlock(&philo->vars->forks[i].mutex);
	pthread_mutex_unlock(&philo->vars->forks[j].mutex);
}
