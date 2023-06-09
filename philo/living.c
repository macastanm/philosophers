/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:38:42 by macastan          #+#    #+#             */
/*   Updated: 2023/06/19 12:39:06 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->died != 0
		|| philo->rules->all_ate == philo->rules->n_philo)
	{
		pthread_mutex_unlock(&philo->rules->verify);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->verify);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_terminal(philo, TAKEN);
		pthread_mutex_lock(philo->l_fork);
		print_terminal(philo, TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_terminal(philo, TAKEN);
		pthread_mutex_lock(philo->r_fork);
		print_terminal(philo, TAKEN);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->died != 0
		|| philo->rules->all_ate == philo->rules->n_philo)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->rules->verify);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->verify);
	eating2(philo);
	return (1);
}

void	eating2(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive);
	print_terminal(philo, EATING);
	philo->lt_eat = gettime();
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->m_eat != 0)
	{
		philo->t_eaten++;
		if (philo->t_eaten == philo->rules->m_eat)
			philo->rules->all_ate++;
	}
	pthread_mutex_unlock(&philo->rules->verify);
	pthread_mutex_unlock(&philo->alive);
	usleep(philo->rules->t_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->died != 0
		|| philo->rules->all_ate == philo->rules->n_philo)
	{
		pthread_mutex_unlock(&philo->rules->verify);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->verify);
	print_terminal(philo, SLEEPING);
	usleep(philo->rules->t_sleep * 1000);
	return (1);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->verify);
	if (philo->rules->died != 0
		|| philo->rules->all_ate == philo->rules->n_philo)
	{
		pthread_mutex_unlock(&philo->rules->verify);
		return (0);
	}
	pthread_mutex_unlock(&philo->rules->verify);
	print_terminal(philo, THINKING);
	return (1);
}
