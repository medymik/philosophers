/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devo <devo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:49:28 by devo              #+#    #+#             */
/*   Updated: 2021/02/17 23:50:52 by devo             ###   ########.fr       */
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

void		*health_check(void *data)
{
	t_philo *p;

	p = data;
	while (1)
	{
		if (get_time() > p->limit)
		{
			print_message(p, DIED);
			sem_post(g_stop);
			return (NULL);
		}
	}
	return (NULL);
}

void		philosophers_routine(t_philo *p)
{
	int eat;

	eat = 0;
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
	pthread_create(&p->health, NULL, health_check, p);
	pthread_detach(p->health);
	while (1)
	{
		sem_wait(g_forks);
		print_message(p, FORK);
		sem_wait(g_forks);
		print_message(p, FORK);
		print_message(p, EAT);
		p->last_meal = get_time();
		p->limit = p->last_meal + g_die;
		eat++;
		usleep(EAT_TIME);
		sem_post(g_forks);
		sem_post(g_forks);
		if (g_eat_count != -1 && eat == g_eat_count)
		{
			sem_post(g_seat_count);
			exit(0);
		}
		print_message(p, SLEEP);
		usleep(SLEEP_TIME);
		print_message(p, THINK);
	}
	exit(0);
}
