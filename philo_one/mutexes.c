/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:14:12 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 08:15:15 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	mutexes_init(void)
{
	int i;

	g_forks = malloc(sizeof(pthread_mutex_t) * g_n);
	pthread_mutex_init(&g_io_lock, NULL);
	i = -1;
	while (++i < g_n)
		pthread_mutex_init(&g_forks[i], NULL);
}

void	mutexes_clear(void)
{
	int i;

	i = -1;
	while (++i < g_n)
		pthread_mutex_destroy(&g_forks[i]);
	pthread_mutex_destroy(&g_io_lock);
	free(g_forks);
}
