/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:38:30 by macastan          #+#    #+#             */
/*   Updated: 2023/06/13 12:38:50 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_join(rules->phi[i].philo, NULL) != 0)
			return (0);
		//usleep(2000);
		i++;
	}
	if (pthread_join(rules->control, NULL) != 0)
		return (0);
	i = 0;
	while (i < rules->n_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->phi[i].alive);
		i++;
	}
	pthread_mutex_destroy(&rules->print);
	pthread_mutex_destroy(&rules->verify);
	return (1);
}

int	creat_thread(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->n_philo)
	{
		if (pthread_create(&rules->phi[i].philo, NULL,
				&living, &rules->phi[i]) != 0)
			return (0);
		usleep(2000);
		i++;
	}
	if (pthread_create(&rules->control, NULL,
			&verify, rules) != 0)
		return (0);
	return (1);
}

int	creat_philos(t_rules *rules, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	rules->phi = malloc(sizeof(t_philo) * rules->n_philo);
	if (rules->phi == NULL)
		return (0);
	while (i < rules->n_philo)
	{
		rules->phi[i].id = i + 1;
		rules->phi[i].t_eaten = 0;
		rules->phi[i].lt_eat = gettime();
		rules->phi[i].r_fork = &forks[i];
		if (i == rules->n_philo - 1)
			rules->phi[i].l_fork = &forks[0];
		else
			rules->phi[i].l_fork = &forks[i + 1];
		rules->phi[i].rules = rules;
		if (pthread_mutex_init(&rules->phi[i].alive, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	creat_forks(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof (pthread_mutex_t) * (rules->n_philo));
	if (!rules->forks)
		return (0);
	while (i < rules->n_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&rules->verify, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&rules->print, NULL) != 0)
		return (0);
	return (1);
}

int	creating(t_rules *rules)
{
	if (creat_forks(rules) != 1)
		return (printf("An error has occurred\n"));
	if (creat_philos(rules, rules->forks) != 1)
		return (printf("An error has occurred\n"));
	if (creat_thread(rules) != 1)
		return (printf("An error has occurred\n"));
	if (join_threads(rules) != 1)
		return (printf("An error has occurred\n"));
	return (1);
}
