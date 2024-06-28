#include "minitalk.h"

void	initalize_struct(int pid, t_signal *client)
{
	if (!client->old_pid)
		client->old_pid = client->pid;
	client->pid = pid;
	client->size = 0;
	client->flag = 0;
	client->bit = 0;
	client->message = 0;
}

size_t	check_process_id(int signum, int pid, t_signal *client)
{
	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (client->pid == pid)
			client->flag++;
		else if (!client->pid)
			client->pid = pid;
		else if (client->pid != pid && client->flag)
			initalize_struct(pid, client);
		else
			client->old_pid = 0;
		if (client->flag == 33)
			ft_putchar('\n');
		if (client->flag > 32)
			return (1);
	}
	return (0);
}

void	ft_kill(int pid, int signum, int flag)
{
	if (kill(pid, signum) == -1)
	{
		if (flag)
		{
			ft_putstr("Error:  Process ID does not exist", 1);
			exit(EXIT_FAILURE);
		}
	}
}

void	send_one_bit(int pid, int bit, int flag)
{
	if (bit)
		ft_kill(pid, SIGUSR1, flag);
	else
		ft_kill(pid, SIGUSR2, flag);
}
