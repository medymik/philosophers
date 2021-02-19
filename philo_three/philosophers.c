/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devo <devo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:49:28 by devo              #+#    #+#             */
/*   Updated: 2021/02/19 01:59:58 by devo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		philosophers_init(void)
{
	int i;

	i = 0;
	g_ps = malloc(sizeof(t_philo) * g_n);
	while (i < g_n)
	{
		g_ps[i].id = i;
		i++;
	}
}

void		philosophers_start(void)
{
	int i;

	i = -1;
	g_start = get_time();
	while (++i < g_n)
	{
		g_ps[i].pid = fork();
		if (!g_ps[i].pid)
		{
			philosophers_routine(&g_ps[i]);
			exit(0);
		}
		usleep(100);
	}
}

void		release_fork(void)
{
	sem_post(g_forks);
	sem_post(g_forks);
}

void		philosophers_routine(t_philo *p)
{
	int eat;

	init_time_monitor(p);
	eat = 0;
	while (1)
	{
		sem_wait(g_forks);
		print_message(p, FORK);
		sem_wait(g_forks);
		print_message(p, FORK);
		print_message(p, EAT);
		set_new_time(p);
		eat++;
		usleep(g_eat);
		release_fork();
		if (g_eat_count != -1 && eat == g_eat_count)
		{
			sem_post(g_seat_count);
			exit(0);
		}
		print_message(p, SLEEP);
		usleep(g_sleep);
		print_message(p, THINK);
	}
}
