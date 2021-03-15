/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devo <devo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 23:39:36 by devo              #+#    #+#             */
/*   Updated: 2021/03/15 13:49:52 by devo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval n;

	gettimeofday(&n, NULL);
	return ((n.tv_sec * 1000) + (n.tv_usec * 0.001));
}

void			semaphores_init(void)
{
	sem_unlink("/forks");
	sem_unlink("/stop");
	sem_unlink("/g_io_lock");
	sem_unlink("/g_eat_count");
	g_seat_count = sem_open("/g_eat_count", O_CREAT, 0600, 0);
	g_forks = sem_open("/forks", O_CREAT, 0600, g_n);
	g_stop = sem_open("/stop", O_CREAT, 0600, 0);
	g_io_lock = sem_open("/g_io_lock", O_CREAT, 0600, 1);
}

void			*mounitor(void *data)
{
	int i;

	i = -1;
	while (++i < g_n)
		sem_wait(g_seat_count);
	sem_post(g_stop);
	return (data);
}

void			init_prog(int argc, char **argv)
{
	g_n = ft_atoi(argv[1]);
	g_die = ft_atoi(argv[2]);
	g_eat = ft_atoi(argv[3]) * 1000;
	g_sleep = ft_atoi(argv[4]) * 1000;
	g_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
}

int				main(int argc, char **argv)
{
	pthread_t	th_monitor;
	int			i;

	if (!args_isvalid(argc, argv))
	{
		print_error("Error : arguments are not valid\n");
		return (1);
	}
	init_prog(argc, argv);
	philosophers_init();
	semaphores_init();
	philosophers_start();
	pthread_create(&th_monitor, NULL, mounitor, NULL);
	pthread_detach(th_monitor);
	sem_wait(g_stop);
	i = 0;
	// while (++i < g_n)
	// 	kill(g_ps[i].pid, SIGKILL);
	free(g_ps);
	sem_close(g_forks);
	sem_close(g_stop);
	sem_close(g_io_lock);
	sem_close(g_seat_count);
	sem_destroy(g_forks);
	sem_destroy(g_stop);
	sem_destroy(g_io_lock);
	sem_destroy(g_seat_count);
	return (0);
}
