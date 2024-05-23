#include "minitalk.h"

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putstr(char *str) {
	while (*str) {
		ft_putchar(*str);
		str++;
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


