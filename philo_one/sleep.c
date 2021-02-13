/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:34:21 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 08:35:38 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		go_sleep(t_philo *p)
{
	int time;

	time = g_sleep * 1000;
	if (g_someone_died)
	{
		print_message(p, SLEEP);
		usleep(time);
		return (1);
	}
	return (0);
}
