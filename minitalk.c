#include "minitalk.h"

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(unsigned int nbr) {
	if (nbr > 9) {
		ft_putnbr(nbr / 10);
	}
	ft_putchar("0123456789"[nbr % 10]);
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

int	ft_atoi(char *str) {
	int	result;

	result = 0;
	while (*str && (*str == ' ' || *str == '\t')) {
		str++;
	}
	if (*str == '-') {
		return (0);
	}
	if(*str == '+') {
		str++;
	}
	while (*str && *str >= '0' && *str <= '9') {
		result = result * 10 + *str - 48;
		str++;
	}
	if (*str) {
		return (0);
	}
	return (result);
}

void	ft_kill(int pid, int signum) {
	if (kill(pid, signum) == -1) {
		ft_putstr("error:  process ID is not a valid", 1);
		exit(EXIT_FAILURE);
	}
}

void	send_one_bit(int pid, bool bit) {
	if (bit) {
		ft_kill(pid, SIGUSR1);
	}
	else {
		ft_kill(pid, SIGUSR2);
	}
}
