#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_signal
{
	int		pid;
	int		old_pid;
	size_t	size;
	size_t	flag;
	size_t	bit;
	char	message;
}		t_signal;

// utils.c
void	ft_putchar(char c);
void	ft_putnbr(size_t nbr);
void	ft_putstr(char *str, size_t nbr);
size_t	ft_strlen(char *str);
int		ft_atoi(char *str);

// minital.c
void	initalize_struct(int pid, t_signal *client, bool flag);
size_t	check_process_id(int signum, int pid, t_signal *client);
size_t	handle_arguments(int argc, char **argv, int *pid);
void	ft_kill(int pid, int signum, bool flag);
void	send_one_bit(int pid, int bit, bool flag);

// client.c
//	void	signal_handler(int signum);
void	send_one_byte(int pid, char message);
void	send_message(int pid, char *message);
void	send_size_off_message(int pid, size_t message_size);

// server.c
//	void	signal_handler(int signum, siginfo_t *info, void *context);
void	receive_message(int signum, t_signal *client);
void	receive_size_of_message(int signum, t_signal *client);
void	signal_configuration(void);
#endif
