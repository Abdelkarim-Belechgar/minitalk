#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_signal	client;
	size_t		error;

	(void)context;
	error = 0;
	usleep(100);
	if (info->si_pid)
	{
		error = check_process_id(signum, info->si_pid, &client);
		if (error)
			receive_message(signum, &client);
		else
			receive_size_of_message(signum, &client);
		if (client.old_pid)
			send_one_bit(client.old_pid, client.bit, 0);
		else
			send_one_bit(client.pid, client.bit, 0);
	}
}

void	receive_message(int signum, t_signal *client)
{
	static int	bit;

	if (signum == SIGUSR1)
		client->message |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		ft_putchar(client->message);
		bit = 0;
		client->message = 0;
		client->size--;
		if (!client->size)
			client->pid = 0;
	}
	client->bit = 1;
}

void	receive_size_of_message(int signum, t_signal *client)
{
	if (client->flag && (signum == SIGUSR1 || signum == SIGUSR2))
	{
		if (signum == SIGUSR1)
			client->size |= (1 << (32 - client->flag));
	}
	client->bit = 1;
}

void	signal_configuration(void)
{
	struct sigaction	sa;

	ft_putstr("server process ID", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Error: Sigaction()=Failed to change the action from SIGUSR1", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error: Sigaction()=Failed to change the action from SIGUSR2", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	signal_configuration();
	while (1)
		pause();
}
