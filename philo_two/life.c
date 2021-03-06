/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:36:03 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 09:51:45 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void			*check_health(void *data)
{
	t_philo *p;

	p = data;
	while (g_someone_died)
	{
		if (p->eat_count != -1 && p->eat_count == g_count)
		{
			return (NULL);
		}
		if (!p->eating && get_time() > p->limit)
		{
			print_message(p, DIED);
			g_someone_died = 0;
			sem_post(g_forks);
			sem_post(g_forks);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

static void		generate_health_checker(t_philo *p)
{
	pthread_create(&p->th_health, NULL, check_health, p);
	pthread_detach(p->th_health);
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
}

void			*philosophers_routine(void *data)
{
	t_philo *p;

	p = data;
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
	generate_health_checker(p);
	while (g_someone_died)
	{
		if (!take_fork(p))
			return (NULL);
		if (!eat(p))
			return (NULL);
		if (!release_fork())
			return (NULL);
		p->eat_count++;
		if (g_count != -1 && p->eat_count == g_count)
		{
			g_eat_count++;
			return (NULL);
		}
		if (!go_sleep(p))
			return (NULL);
		print_message(p, THINK);
	}
	return (NULL);
}
