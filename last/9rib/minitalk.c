#include "minitalk.h"

void	ft_kill(int pid, int signum, bool flag)
{
	if (kill(pid, signum) == -1)
	{
		//	flag true exit client || flag false does not exit;
		if (flag)
		{
			ft_putstr("error:  process ID does not exist", 1);
			exit(EXIT_FAILURE);
		}
		else
			ft_putstr("", 1);
	}
}

void	send_one_bit(int pid, bool bit, bool flag)
{
	if (bit)
		ft_kill(pid, SIGUSR1, flag);
	else
		ft_kill(pid, SIGUSR2, flag);
}
