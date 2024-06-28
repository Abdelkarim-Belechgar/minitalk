#include "minitalk.h"

void	initalize_struct_for_new_pid(int *tmp, int pid, t_signal *client)
{
	if (client->flag)
		*tmp = 0;
	if (!*tmp && pid)
	{
		*tmp = client->pid;
		client->pid = pid;
		client->size = 0;
		client->flag = 0;
		client->bit = 0;
		client->message = 0;
		if (*tmp)
			send_one_bit(*tmp, 0, 0);
	}
}

size_t	check_process_id(int signum, int pid, t_signal *client)
{
	static int	tmp;

	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		if (client->pid == pid)
			client->flag++;
		else if (client->pid != pid && pid)
		{
			ft_putstr("\n**** inital ****", tmp);
			ft_putnbr(pid);
			initalize_struct_for_new_pid(&tmp, pid, client);
		}
		else
		{
			ft_putstr("\n\n*** error ***\n", 1);
			ft_putstr("pid ", pid);
			ft_putstr("client->pid", client->pid);
			ft_putstr("client->flag", client->flag);
		}
		if (client->flag == 33)
			ft_putchar('\n');
		if (client->flag > 32)
			return (1);
	}
	return (0);
}

size_t	handle_arguments(int argc, char **argv, int *pid)
{
	size_t	size;

	if (argc != 3)
	{
		ft_putstr("Error:  Number of arguments not valid", 1);
		exit (EXIT_FAILURE);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid < 2 || !*argv[2])
	{
		if (!*argv[2])
			ft_putstr("Error:  Empty message", 1);
		if (*pid < 2)
			ft_putstr("Error:  Process ID is not a valid", 1);
		exit (EXIT_FAILURE);
	}
	ft_kill(*pid, SIGUSR1, 1);
	pause();
	usleep(100);
	size = ft_strlen(argv[2]);
	return (size);
}

void	ft_kill(int pid, int signum, bool flag)
{
	if (kill(pid, signum) == -1)
	{
		if (flag)
		{
			ft_putstr("Error:  Process ID does not exist", 1);
			exit(EXIT_FAILURE);
		}
		else
			ft_putchar('\n');
	}
}

void	send_one_bit(int pid, bool bit, bool flag)
{
	if (bit)
		ft_kill(pid, SIGUSR1, flag);
	else
		ft_kill(pid, SIGUSR2, flag);
}
