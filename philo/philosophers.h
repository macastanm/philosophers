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

typedef struct s_times
{
	int	n_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	m_eat;
}		t_times;

// philosophers.c

void	init_times(t_times *times, char **argv, int argc);
int		check_args(int argc, char **argv);

// utils.c

long	ft_atoi(const char *str);
int		ft_ispos(int argc, char **argv);
int		ft_isnum(int argc, char **argv);
int		ft_isbig(int argc, char **argv);

#endif
