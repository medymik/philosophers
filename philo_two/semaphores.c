/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devo <devo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:14:12 by mymik             #+#    #+#             */
/*   Updated: 2021/02/15 03:14:53 by devo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	semaphores_init(void)
{
	semaphores_clear();
	g_forks = sem_open("forks", O_CREAT, 0600, g_n);
	g_io_lock = sem_open("io_lock", O_CREAT, 0600, 1);
}

void	semaphores_clear(void)
{
	sem_close(g_forks);
	sem_unlink("forks");
	sem_close(g_io_lock);
	sem_unlink("io_lock");
}
