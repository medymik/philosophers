/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mymik <mymik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 08:11:37 by mymik             #+#    #+#             */
/*   Updated: 2021/02/13 08:12:02 by mymik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_isnumeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}

int		ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long			value;
	long			prev;

	i = 0;
	sign = 1;
	value = 0;
	while (((str[i] <= 13 && str[i] >= 9) || str[i] == 32) && str[i] != '\0')
		i++;
	if (str[i] == '-' || str[i] == '+')
		(str[i++] == '-') ? sign = -1 : 1;
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		prev = value;
		value = value * 10 + sign * (str[i] - '0');
		if (sign == 1 && prev > value)
			return (-1);
		else if (sign == -1 && prev < value)
			return (0);
		i++;
	}
	return (value);
}

void	ft_putnbr_fd(unsigned long long n, int fd)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
