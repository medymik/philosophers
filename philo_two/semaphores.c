/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:14:12 by mymik             #+#    #+#             */
/*   Updated: 2021/02/19 08:27:28 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	semaphores_init(void)
{
	sem_unlink("forks");
	sem_unlink("io_lock");
	g_forks = sem_open("forks", O_CREAT, 0600, g_n);
	g_io_lock = sem_open("io_lock", O_CREAT, 0600, 1);
}
