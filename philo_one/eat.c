/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:19:04 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 08:32:16 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		eat(t_philo *p)
{
	int time;

	time = g_eat * 1000;
	if (g_someone_died == 1)
	{
		pthread_mutex_lock(&p->mutex);
		p->eating = 1;
		print_message(p, EAT);
		p->last_meal = get_time();
		p->limit = p->last_meal + g_die;
		p->eating = 0;
		usleep(time);
		pthread_mutex_unlock(&p->mutex);
		return (1);
	}
	return (0);
}
