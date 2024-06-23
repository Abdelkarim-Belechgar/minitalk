#include "minitalk.h"

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
	}
	send_one_bit(client->pid, 1, 0);
}

void	receive_size_of_message(int signum, t_signal *client)
{
	ft_putstr("client pid", client->pid);
	ft_putstr("client flag", client->flag);
	if (client->flag && (signum == SIGUSR1 || signum == SIGUSR2))
	{
		if (signum == SIGUSR1)
			client->size |= (1 << (32 - client->flag));
		ft_putstr("flag", client->flag);
		ft_putstr("new size", client->size);
		if (client->flag == 32)
			ft_putstr("size of message hase ben send", client->size);
	}
	send_one_bit(client->pid, 1, 0);
}

size_t	check_processID(int signum, int pid, t_signal *client)
{
	int	tmp;

	tmp = 0;
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (!client->pid)
			client->pid = pid;
		else if (client->pid == pid)
			client->flag++;
		else if (client->pid != pid && !client->pid)
		{
			ft_putstr("initalaiz", pid);
			tmp = client->pid;
			client->size = 0;
			client->flag = 0;
			client->bit = 0;
			client->message = 0;
			client->pid = pid;
			ft_putstr("befor", client->pid);
			send_one_bit(tmp, 0, 0);
			ft_putstr("after", client->pid);
		}
		if (client->flag > 32)
			return (1);
	}
	return (0);
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static t_signal	client;

	(void)context;
	usleep(300);
	if (check_processID(signum, info->si_pid, &client))
		receive_message(signum, &client);
	else
		receive_size_of_message(signum, &client);
}

void	signal_configuration(void)
{
	struct sigaction	sa;

	ft_putstr("server process ID", getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("error: sigaction()=Failed to change the action from SIGUSR1", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("error: sigaction()=Failed to change the action from SIGUSR2", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	signal_configuration();
	while (1)
		pause();
}
