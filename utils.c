#include "philosophers.h"

int	ft_isnumeric(char *str)
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


void		ft_putnbr_fd(unsigned long long n, int fd)
{
	char		tmp;
	unsigned long long nb;

	nb = n;
	if (nb < 0)
	{
		tmp = '-';
		write(fd, &tmp, 1);
		nb = nb * -1;
	}
	if (nb < 10)
	{
		tmp = nb + 48;
		write(fd, &tmp, 1);
	}
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
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