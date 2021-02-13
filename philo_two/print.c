/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:13:39 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 09:25:16 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_error(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		write(1, &str[i], 1);
	}
}

void	print_format(int state)
{
	if (state == EAT)
		ft_putstr(" is eating\n");
	else if (state == SLEEP)
		ft_putstr(" is sleeping\n");
	else if (state == THINK)
		ft_putstr(" is thinking\n");
	else if (state == DIED)
		ft_putstr(" died\n");
	else if (state == FORK)
		ft_putstr(" has taken a fork\n");
}

void	print_message(t_philo *p, int state)
{
	sem_wait(g_io_lock);
	ft_putnbr_fd(get_time() - g_start, 1);
	ft_putstr(" ");
	ft_putnbr_fd(p->id + 1, 1);
	print_format(state);
	if (state != DIED)
		sem_post(g_io_lock);
}
