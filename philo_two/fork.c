/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:17:27 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 09:16:23 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		take_fork(t_philo *p)
{
	if (g_someone_died)
	{
		sem_wait(g_forks);
		print_message(p, FORK);
		if (g_someone_died)
		{
			sem_wait(g_forks);
			print_message(p, FORK);
			return (1);
		}
	}
	return (0);
}

int		release_fork(void)
{
	if (g_someone_died)
	{
		sem_post(g_forks);
		sem_post(g_forks);
		return (1);
	}
	return (0);
}
