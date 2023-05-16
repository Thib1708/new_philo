/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:47:36 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/05/16 14:54:55 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo **philo, t_args *args, int *n_eat)
{
	int i;
	
	i = -1;
	while (++i < args->nb_philo)
	{
		if (ft_current_time(args->time) - philo[i]->t_last_eat > args->t_die)
		{
			ft_print(philo[i], "\033[0;31mdied\033[0m");
			args->is_dead = 1;
			return (1);
		}
		pthread_mutex_lock(&args->m_eat);
		if (args->must_eat > -1 && philo[i]->nb_eat >= args->must_eat)
			*n_eat += 1;
		pthread_mutex_unlock(&args->m_eat);
	}
	return (0);
}

int	ft_check_philo(t_philo **philo, t_args *args)
{
	int n_eat;
	
	while (1)
	{
		n_eat = 0;
		pthread_mutex_lock(&args->m_stop);
		if (ft_check_death(philo, args, &n_eat))
		{
			pthread_mutex_unlock(&args->m_stop);
			return (1);
		}
		pthread_mutex_unlock(&args->m_stop);
		if (args->nb_philo == n_eat)
		{
			args->is_dead = 1;
			return (1);
		}
	}
	return (0);
}