#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putstr(char *str) {
	while (*str) {
		ft_putchar(*str);
		str++;
	}
}

void	ft_putnbr(int nbr) {
	if (nbr > 9) {
		ft_putnbr(nbr / 10);
	}
	nbr %= 10;
	ft_putchar(nbr + 48);
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

unsigned int	convert_decimal_to_binary(char *str, unsigned char c) {
	unsigned int	byte;
	unsigned int	res;
	unsigned int	z;

	z = 8;
	res = 0;
	byte = 128;
	initialisation_string(str);
	while (z--) {
		if (c >= byte) {
			res++;
			*str = '1';
			c -= byte;
		}
		byte /= 2;
		str++;
	}
}

void	send_one_byte(pid_t pid, unsigned int c) {
	unsigned int	byte;
	unsigned int	z;

	z = 8;
	byte = 128;
	while (z--) {
		if (c >= byte && kill(pid, SIGUSR1) != -1) {
			c -= byte;
		}
		else {
			kill(pid, SIGUSR2);
		}
		byte /= 2;
	}

void	send_len_of_message(pid_t pid, unsigned int len) {
	unsigned int	z;
	unsigned char	c;
	char		*ptr;

	z = 4;
	ptr = &pid;
	while (z--) {
		c = *ptr;
		send_one_byte(pid, c);
		ptr++;
	}
}

pid_t	get_pid(int argc, char **argv) {
	pid_t	pid;

	if (argc == 3) {
		if ((pid = ft_atoi(argv[1])) < 2 ) {
			ft_putstr("pid error\n");
			exit (1);
		}
		if (!*argv[2]) {
			ft_putstr("empty message\n");
			exit(1);
		}
		ft_putstr("\"sender\"\t==> Client PID = ");
		ft_putnbr(getpid());
		ft_putstr("\n\"receiver\"\t==> Server PID = ");
		ft_putnbr(pid);
	}
	else {
		ft_putstr("error number of arguments\n");
		exit(1);
	}
	return (pid);
}

int	main(int argc, char **argv) {
<<<<<<< HEAD
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
=======
	pid_t		pid;
	unsigned int	len;

	pid = get_pid(argc, argv);
	len = ft_strlen(argv[2]);
	send_len_of_message(len, pid);
>>>>>>> 82e495c82c5938205bf8629516cb76eabd8c3741
	return (0);
}
//	char		*binary;
//	binary = (char *)malloc(sizeof(char) * 9);
//	if (!binary) {
//		return (1);
//	}
//	while (*argv[1]) {
//		convert_decimal_to_binary(binary, *argv[1]);
//		printf("str '%c' new = %s\n", *argv[1], binary);
//		res = convert_binary_to_decimal(binary);
//		printf("res = %u\n", res);
//		argv[1]++;
//	}
//	free(binary);
