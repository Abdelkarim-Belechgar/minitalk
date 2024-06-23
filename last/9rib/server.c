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

void	receive_size_of_message(int signum, int pid, t_signal *client)
{
	if (client->new_flag && (signum == SIGUSR1 || signum == SIGUSR2))
	{
		if (signum == SIGUSR1)
			client->new_size |= (1 << (32 - client->new_flag));
		ft_putstr("flag", client->flag);
		ft_putstr("new flag", client->new_flag);
		ft_putstr("new size", client->size);
		if (client->new_flag == 32)
		{
			if (client->pid)
				send_one_bit(client->pid, 0, 0);
			client->flag = client->new_flag;
			client->new_flag = 0;
			client->pid = client->new_pid;
			client->new_pid = 0;
			client->size = client->new_size;
			client->new_size = 0;
			client->error = 0;
			client->bit = 0;
			client->message = 0;
			ft_putstr("size of message hase ben send", client->size);
		}
	}
	usleep(50);
	send_one_bit(pid, 1, 0);
}

size_t	check_processID(int signum, int pid, t_signal *client)
{
	size_t	flag;

	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		flag = client->flag;
		if (client->pid == pid)
			client->flag++;
		else if (client->new_pid == pid)
			client->new_flag++;
		else if (!client->pid || !client->new_pid)
			client->new_pid = pid;
		if (flag != client->flag)
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
		receive_size_of_message(signum, info->si_pid, &client);
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
