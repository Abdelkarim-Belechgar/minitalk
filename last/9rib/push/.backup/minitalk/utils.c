#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(size_t nbr)
{
	if (nbr > 9)
		ft_putnbr(nbr / 10);
	ft_putchar("0123456789"[nbr % 10]);
}

void	ft_putstr(char *str, size_t nbr)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
	if (nbr > 1)
	{
		ft_putstr(" :  ", 0);
		ft_putnbr(nbr);
	}
	if (nbr)
		ft_putchar('\n');
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}

int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	if (*str)
		return (0);
	return (result);
}
