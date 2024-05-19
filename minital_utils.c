//#include "minitalk.h"
#include <unistd.h>
void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putstr(char *str) {
	if (!str) {
		write(1, "(null)\n", 7);
	}
	else {
		while (*str) {
			ft_putchar(*str);
			str++;
		}
	}
}

int	ft_atoi(char *str) {
	int	result;
	int	sign;


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

#include <stdlib.h>
char*	convert_string_byts(char c) {
	char	*str;
	int		byte;
	int		z;

	str = malloc(9);
	z = 0;
	while (8 > z) {
		str[z] = 48;
		z++;
	}
	str[z] = 0;
	z = 8;
	byte = 128;
	while (z--) {
		if (c >= byte) {
			*str = '1';
			c -= byte;
		}
		str++;
		byte /= 2;
	}
	return (str - 8);
}

#include <stdio.h>
int	main(void) {
	char *emoji = "a😀z";
	char	*str = convert_string_byts('a');
	ft_putstr(str);
	ft_putchar('\n');
	ft_putstr(emoji);
	ft_putchar('\n');
	printf("%u\n", ft_strlen(emoji));
}
