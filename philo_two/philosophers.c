/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:40:46 by mymik             #+#    #+#             */
/*   Updated: 2021/02/19 08:24:35 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers_init(void)
{
	int i;

	g_ps = malloc(sizeof(t_philo) * g_n);
	i = -1;
	semaphores_init();
	while (++i < g_n)
	{
		g_ps[i].eat_count = 0;
		g_ps[i].id = i;
		g_ps[i].left = i;
		g_ps[i].right = (i + 1) % g_n;
	}
	g_someone_died = 1;
}

void	philosophers_start(void)
{
	int i;

	g_start = get_time();
	i = -1;
	while (++i < g_n)
	{
		pthread_create(&g_ps[i].th, NULL, philosophers_routine, &g_ps[i]);
		pthread_detach(g_ps[i].th);
		usleep(100);
	}
}

void	philosophers_clear(void)
{
	free(g_ps);
	sem_unlink("forks");
	sem_unlink("io_lock");
}
