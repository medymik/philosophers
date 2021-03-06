/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:40:54 by mymik             #+#    #+#             */
/*   Updated: 2021/02/19 07:58:32 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (!args_isvalid(argc, argv))
	{
		print_error("Error : arguments are not valid\n");
		return (1);
	}
	g_n = ft_atoi(argv[1]);
	g_die = ft_atoi(argv[2]);
	g_eat = ft_atoi(argv[3]);
	g_sleep = ft_atoi(argv[4]);
	g_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
	philosophers_init();
	philosophers_start();
	while (g_someone_died && g_eat_count != g_n)
		usleep(2000);
	philosophers_clear();
	return (0);
}
