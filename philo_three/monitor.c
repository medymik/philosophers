/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devo <devo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 01:30:22 by devo              #+#    #+#             */
/*   Updated: 2021/02/19 01:30:22 by devo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void		init_time_monitor(t_philo *p)
{
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
	pthread_create(&p->health, NULL, health_check, p);
	pthread_detach(p->health);
}

void		set_new_time(t_philo *p)
{
	p->last_meal = get_time();
	p->limit = p->last_meal + g_die;
}
