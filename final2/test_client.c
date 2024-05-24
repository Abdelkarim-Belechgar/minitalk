#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void	send_bits(int pid, char msg) {
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (msg >> bit & 1)
			kill(pid, SIGUSR2);
		else
		{
			kill(pid, SIGUSR1); 
		}
		bit--;
		usleep(300);
	}
}

int	main(int ac, char **av)
{
	int	pid;

	(void)ac;
	pid = atoi(av[1]);
	send_bits(pid, *av[2]);
	return (0);
}
