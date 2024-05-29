#ifndef	MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	t_signal {
	int	pid;
	int	size;
	int	flag;
	int	error;
	char	*message;
} 		info_signal;

// minital.c
void		ft_putchar(char c);
void		ft_putnbr(int nbr);
void		ft_putstr(char *str, int nbr);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void		ft_kill(int pid, int signum);
void		send_one_bit(int pid, bool bit);
// client.c

// server.c

#endif
