#ifndef	MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	s_signal {
	int		pid;
	int		new_pid;
	size_t	size;
	size_t	new_size;
	size_t	flag;
	size_t	new_flag;
	size_t	error;
	int		bit;
	unsigned char	message;
}		t_signal;

// utils.c		// done
void	ft_putchar(char c);
void	ft_putnbr(size_t nbr);
void	ft_putstr(char *str, size_t nbr);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);

// minital.c
void		ft_kill(int pid, int signum, bool flag);
void		send_one_bit(int pid, bool bit, bool flag);

// client.c

// server.c
// void	signal_handler(int signum, siginfo_t *info, void *conte);
// int	check_processID(int signum, int pid, t_signal *client);

#endif
