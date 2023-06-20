/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 11:34:47 by macastan          #+#    #+#             */
/*   Updated: 2023/05/30 11:35:00 by macastan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_terminal(philo, TAKEN);
	pthread_mutex_unlock(&philo->r_fork);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Please, check the number of arguments!\n");
		return (0);
	}
	if (ft_isnum(argc, &*argv) != 1)
	{
		printf("Please, arguments must be only numbers!\n");
		return (0);
	}
	if (ft_ispos(argc, &*argv) != 1)
	{
		printf("Please, the numbers must be bigger then zero!\n");
		return (0);
	}
	if (ft_isbig(argc, &*argv) != 1)
	{
		printf("Please, the numbers are too big!\n");
		return (0);
	}
	return (1);
}

void	init_times(t_rules *rules, char **argv, int argc)
{
	rules->n_philo = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->t_eat = ft_atoi(argv[3]);
	rules->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->m_eat = ft_atoi(argv[5]);
	else
		rules->m_eat = 0;
	rules->t_start = gettime();
	rules->died = 0;
	rules->all_ate = 0;
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (check_args(argc, &*argv) != 1)
		return (0);
	rules = malloc(sizeof(t_rules));
	if (rules == NULL)
		return (printf("An error has occurred\n"));
	init_times(rules, &*argv, argc);
	creating(rules);
	free(rules->forks);
	free(rules->phi);
	free(rules);
	return (0);
}
