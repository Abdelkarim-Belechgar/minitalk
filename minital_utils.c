#include <unistd.h>

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putstr(char *str) {
	while (*str) {
		ft_putchar(*str);
		str++;
	}
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

void	initialisation_string(char *str) {
	unsigned int	z;

	z = 0;
	while (8 > z) {
		str[z] = 48;
		z++;
	}
	str[z] = 0;
}

unsigned int	convert_binary_to_decimal(char *str) {
	unsigned int	result;
	unsigned int	byte;

	byte = 128;
	result = 0;
	while (*str) {
		if (*str == 49) {
			result += byte;
		}
		byte /= 2;
		str++;
	}
	return (result);
}

void	convert_decimal_to_binary(char *str, unsigned char c) {
	unsigned int		byte;
	unsigned int		z;

	z = 8;
	byte = 128;
	initialisation_string(str);
	while (z--) {
		if (c >= byte) {
			*str = '1';
			c -= byte;
		}
		byte /= 2;
		str++;
	}
}

unsigned int	handling_args(int argc, char **argv) {
	unsigned int	pid;
	
	if (argc == 3) {
		if ((pid = ft_atoi(argv[1])) < 2 ) {
			ft_putstr("pid error\n");
			exit (1);
		}
		if (!*argv[2]) {
			ft_putstr("empty message\n");
			exit(1);
		}
	}
	else {
		ft_putstr("error number of arguments\n");
		exit(1);
	}
	return (pid);
}

char	*strjoin();
#include <stdio.h>
#include <stdlib.h>
int	main(int argc, char **argv) {
	ft_putstr("世界您好");
	printf("\n%d\n", ft_strlen("世界您好"));
	/*
	pid_t			pid;
	unsigned int	res;
	char			*binary;

	pid = hanling_args(argc, argv);
	while (*argv[1]) {
		convert_decimal_to_binary(binary, *argv[1]);
		printf("str '%c' new = %s\n", *argv[1], binary);
		res = convert_binary_to_decimal(binary);
		printf("res = %u\n", res);
		argv[1]++;
	}
	free(binary);
	*/
	return (0);
}
