#include "minitalk.h"
#include <stdio.h>

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(unsigned int nbr) {
	if (nbr > 9) {
		ft_putnbr(nbr / 10);
	}
	nbr %= 10;
	nbr += 48;
	ft_putchar(nbr);
}

void	ft_putstr(char *str, unsigned int nbr) {
	while (*str) {
		ft_putchar(*str);
		str++;
	}
	if (nbr > 1) {
		ft_putstr(" = ", 0);
		ft_putnbr(nbr);
	}
	if (nbr) {
		ft_putchar('\n');
	}
}

unsigned int	ft_strlen(char *str) {
	unsigned int	len;

	len = 0;
	if (str) {
		while (str[len]) {
			len++;
		}
	}
	return (len);
}

unsigned int	ft_atoi(char *str) {
	unsigned int	result;
	unsigned int	sign;

	sign = 1;
	result = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (sign * result);
}
/*
int	main(void) {
	ft_putstr("hello", 20);
	return (EXIT_SUCCESS);
}*/
