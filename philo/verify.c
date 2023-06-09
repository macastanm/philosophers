/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:22:55 by macastan          #+#    #+#             */
/*   Updated: 2023/06/20 12:23:03 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*living(void *identification)
{
	t_philo	*philo;

	philo = (t_philo *)identification;
	if (philo->rules->n_philo == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(2000);
	while (1)
	{
		if (grab_fork(philo) == 0)
			return (NULL);
		if (eating(philo) == 0)
			return (NULL);
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
	}
}

void	print_terminal(t_philo *philo, char *arg)
{
	long long	time_now;

	pthread_mutex_lock(&philo->rules->print);
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->died != 0
		|| philo->rules->all_ate == philo->rules->n_philo)
	{
		pthread_mutex_unlock(&philo->rules->print);
		pthread_mutex_unlock(&philo->rules->verify);
		return ;
	}
	time_now = gettime() - philo->rules->t_start;
	printf("%lld %d %s", time_now, philo->id, arg);
	pthread_mutex_unlock(&philo->rules->verify);
	pthread_mutex_unlock(&philo->rules->print);
}

int	is_dead(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->phi[i].alive);
		if ((gettime() - rules->phi[i].lt_eat) > rules->t_die)
		{
			print_terminal(&rules->phi[i], DIED);
			pthread_mutex_lock(&rules->verify);
			rules->died++;
			pthread_mutex_unlock(&rules->verify);
			pthread_mutex_unlock(&rules->phi[i].alive);
			return (0);
		}
		pthread_mutex_unlock(&rules->phi[i].alive);
		i++;
	}
	return (1);
}

int	already_ate(t_rules *rules)
{
	pthread_mutex_lock(&rules->verify);
	if (rules->all_ate == rules->n_philo)
	{
		pthread_mutex_unlock(&rules->verify);
		return (0);
	}
	pthread_mutex_unlock(&rules->verify);
	return (1);
}

void	*verify(void *norm)
{
	t_rules	*rules;

	rules = (t_rules *)norm;
	while (1)
	{
		if (is_dead(rules) == 0)
			return (NULL);
		if (rules->m_eat != 0)
			if (already_ate(rules) == 0)
				return (NULL);
	}
}
