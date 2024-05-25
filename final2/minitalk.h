#ifndef	MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	info_signal {
	unsigned int	pid;
	unsigned int	len;
	unsigned int	flag;
	char		*message;
} 		i_signal;

// minital.c
void		ft_putchar(char c);
void		ft_putnbr(unsigned int nbr);
void		ft_putstr(char *str, unsigned int nbr);
unsigned int	ft_strlen(char *str);
unsigned int	ft_atoi(char *str);
void		ft_kill(unsigned int pid, int signum);

// client.c

// server.c

#endif
