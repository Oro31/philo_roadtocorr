/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/19 09:34:49 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_fork {
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_vars {
	t_fork			*forks;
	pthread_mutex_t	write;
	struct timeval	initial_tmstmp;
	int				play;
	int				id;
	int				nb_arg;
	int				nb_philos;
	long			ttd;
	long			tte;
	long			tts;
	int				nb_must_eat;
	int				nb_philos_satiated;
	int				ret;
}				t_vars;

typedef struct s_philo {
	t_vars			*vars;
	pthread_t		th_philo;
	struct timeval	i_ttmp;
	struct timeval	last_meal;
	struct timeval	t;
	int				nb_eat;
	int				is_must_eat;
	int				nb_must_eat;
	long			tte;
	long			tts;
	long			ttd;
	int				alive;
	int				id;
	int				ret;
}				t_philo;

int		ft_is_num(char *str);
int		ft_is_int(char *str);

void	ft_printf(char *msg, long tmstmp, int i);

int		ft_atoi(const char *nptr);

void	ft_lock_forks_mutex(t_philo *philo, int i);
void	ft_unlock_forks_mutex(t_philo *philo, int i);

long	ft_timediff(struct timeval t0, struct timeval t1);
void	ft_usleep(long ttw, t_philo *philo);
long	ft_ttw_before_trying_to_eat(t_philo *philo);

void	ft_taken_a_fork(t_philo *philo, int i);
void	ft_sleeping(t_philo *philo, int i);
void	ft_eating(t_philo *philo, int i);
void	ft_thinking(t_philo *philo, int i);
void	ft_died(t_philo *philo, int i);

void	ft_satiated(t_philo *philo);
void	ft_dead(t_philo *philo);

int		ft_is_philo_dead(struct timeval last_meal, t_philo *philo);
void	ft_philo_eat(t_philo *philo, int i);
void	ft_philo_sleep(t_philo *philo, int i);
void	ft_play_philo(t_philo *philo, int i);
void	*ft_th_philo(void *p_data);

int		ft_create_philo_th(t_vars *vars, t_philo **philos);
int		ft_init_forks(t_vars *vars);
int		ft_init_vars(t_vars *vars, t_philo **philos, int argc, char **argv);
void	ft_init_philo(t_philo *philo);
void	ft_lock_unlock_vars_mutex(t_vars *vars, int opt);

#endif
