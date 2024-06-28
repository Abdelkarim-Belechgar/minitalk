#include "minitalk_bonus.h"

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
		{
			send_one_bit(client->pid, 0, 0);
			initalize_struct(0, client, 1);
		}
	}
}

void	receive_size_of_message(int signum, t_signal *client)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (signum == SIGUSR1)
			client->size |= (1 << (32 - client->flag));
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_signal	client;
	sigset_t		set;

	(void)context;
	sigemptyset(&set);
	if (info->si_pid)
	{
		if (check_process_id(signum, info->si_pid, &client))
			receive_message(signum, &client);
		else if (client.flag)
			receive_size_of_message(signum, &client);
		else
			sigaddset(&set, signum);
		if (client.old_pid)
		{
			send_one_bit(client.old_pid, 1, 0);
			client.old_pid = 0;
		}
	}
}

void	signal_configuration(void)
{
	struct sigaction	sa;

	ft_putstr("server process ID", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Error: Sigaction() Failed to change the action", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error: Sigaction() Failed to change the action", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	signal_configuration();
	while (1)
		pause();
}
