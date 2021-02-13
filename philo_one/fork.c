/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:17:27 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 08:17:52 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		take_fork(t_philo *p)
{
	if (g_someone_died)
	{
		pthread_mutex_lock(&g_forks[p->left]);
		print_message(p, FORK);
		if (g_someone_died)
		{
			pthread_mutex_lock(&g_forks[p->right]);
			print_message(p, FORK);
			return (1);
		}
	}
	return (0);
}

int		release_fork(t_philo *p)
{
	if (g_someone_died)
	{
		pthread_mutex_unlock(&g_forks[p->left]);
		pthread_mutex_unlock(&g_forks[p->right]);
		return (1);
	}
	return (0);
}
