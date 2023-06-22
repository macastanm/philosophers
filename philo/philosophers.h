/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:38:38 by macastan          #+#    #+#             */
/*   Updated: 2023/05/30 11:38:47 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define TAKEN "has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DIED "died\n"

typedef struct s_philo
{
	pthread_mutex_t	alive;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_rules	*rules;
	pthread_t		philo;
	long long		lt_eat;
	int				id;
	int				t_eaten;
}		t_philo;

typedef struct s_rules
{
	pthread_mutex_t	print;
	pthread_mutex_t	verify;
	pthread_mutex_t	*forks;
	pthread_t		control;
	t_philo			*phi;
	long long		t_start;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				m_eat;
	int				died;
	int				all_ate;
}		t_rules;

// philosophers.c

void		one_philo(t_philo *philo);
void		init_times(t_rules *rules, char **argv, int argc);
int			check_args(int argc, char **argv);

// utils.c

long		ft_atoi(const char *str);
long long	gettime(void);
int			ft_ispos(int argc, char **argv);
int			ft_isnum(int argc, char **argv);
int			ft_isbig(int argc, char **argv);

// creating.c

int			creating(t_rules *rules);
int			creat_forks(t_rules *rules);
int			creat_philos(t_rules *rules, pthread_mutex_t *forks);
int			creat_thread(t_rules *rules);
int			join_threads(t_rules *rules);

// living.c

void		*living(void *identification);
int			thinking(t_philo *philo);
int			sleeping(t_philo *philo);
int			eating(t_philo *philo);
int			grab_fork(t_philo *philo);

// verify.c

void		*verify(void *norm);
void		print_terminal(t_philo *philo, char *arg);
int			is_dead(t_rules *rules);
int			already_ate(t_rules *rules);

#endif
