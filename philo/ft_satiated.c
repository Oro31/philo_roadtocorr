/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satiated.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:13:31 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/19 08:02:38 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_satiated(t_philo *philo)
{
	philo->nb_eat++;
	if (philo->nb_eat == philo->nb_must_eat)
		philo->vars->nb_philos_satiated++;
	if (philo->vars->nb_philos_satiated == philo->vars->nb_philos)
	{
		philo->alive = 0;
		philo->vars->play = 0;
	}
}

void	ft_dead(t_philo *philo)
{
	if (philo->vars->play == 0)
		philo->alive = 0;
}
