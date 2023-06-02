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

void	init_times(t_times *times, char **argv, int argc)
{
	times->n_philo = ft_atoi(argv[1]);
	times->t_die = ft_atoi(argv[2]);
	times->t_eat = ft_atoi(argv[3]);
	times->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		times->m_eat = ft_atoi(argv[5]);
	else
		times->m_eat = 0;
}

int	main(int argc, char **argv)
{
	t_times	times;

	if (check_args(argc, &*argv) != 1)
		return (0);
	init_times(&times, &*argv, argc);
	return (0);
}
