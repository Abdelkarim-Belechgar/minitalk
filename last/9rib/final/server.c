#include "minitalk.h"

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_signal	client;

	(void)context;
	usleep(25);
	if (check_process_id(signum, info->si_pid, &client))
		receive_message(signum, &client);
	else
	{
		ft_putstr("pid", info->si_pid);
		if (!info->si_pid)
			ft_putchar('\n');
		ft_putstr("client.pid", client.pid);
		if (!client.pid)
			ft_putchar('\n');
		ft_putstr("client.flag", client.flag);
		if (!client.flag)
			ft_putchar('\n');
		receive_size_of_message(signum, &client);
	}
}

void	receive_message(int signum, t_signal *client)
{
	if (signum == SIGUSR1)
		client->message |= (1 << (7 - client->bit));
	client->bit++;
	if (client->bit == 8)
	{
		ft_putchar(client->message);
		client->message = 0;
		client->bit = 0;
		client->size--;
		if (!client->size)
			send_one_bit(client->pid, 0, 0);
	}
	send_one_bit(client->pid, 1, 0);
}

void	receive_size_of_message(int signum, t_signal *client)
{
	if (client->flag && (signum == SIGUSR1 || signum == SIGUSR2))
	{
		if (signum == SIGUSR1)
			client->size |= (1 << (32 - client->flag));
	}
	if (client->pid)
		send_one_bit(client->pid, 1, 0);
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
