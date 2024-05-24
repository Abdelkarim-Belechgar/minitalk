#include "minitalk.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

static i_signal	client;

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(unsigned int nbr) {
	if (nbr > 9) {
		ft_putnbr(nbr / 10);
	}
	nbr %= 10;
	nbr += 48;
	ft_putchar(nbr);
}

void	ft_putstr(char *str, unsigned int nbr) {
	while (*str) {
		ft_putchar(*str);
		str++;
	}
	if (nbr > 1) {
		ft_putstr(" = ", 0);
		ft_putnbr(nbr);
	}
	if (nbr) {
		ft_putchar('\n');
	}
}
void	handler_msg(int sig_msg, siginfo_t *info, void *notg)
{
//	static char		chr = 0;
//	static int		client_pid;
//	static int		last_pid;
//	static int		cnt = 7;


	(void)notg;
	if (!client.si_pid) {
		client.si_pid = info->si_pid;
	}
	if ((int)client.si_pid == info->si_pid) {
		if (sig_msg == SIGUSR1) {
			ft_putchar('1');
		}
		else {
			ft_putchar('0');
		}
	}
	else {
		ft_putchar('2');
	}
//	ft_putstr("--- start function handeler_message ---", 1);
	/*if (client_pid != last_pid)
	{
		last_pid = client_pid;
		cnt = 7;
		chr = 0;
	}
	if (sig_msg == SIGUSR2)
		chr |= (1 << cnt);
	cnt--;
	if (cnt == -1)
	{
		ft_putstr("+++ message = ", 0);
		ft_putchar(chr);
		ft_putstr("+++", 1);
		chr = 0;
		cnt = 7;
	}*/
//	ft_putstr("--- end function handeler_message ---", 1);
}

void	signal_config(void)
{
	struct sigaction	action;

	ft_putstr("*** start function signal config ***", 1);
	action.sa_sigaction = &handler_msg;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR2, &action, 0) == -1)
		write(1, "Error\n", 6);
	if (sigaction(SIGUSR1, &action, 0) == -1)
		write(1, "Error SIGUSR2\n", 6);
	ft_putstr("*** end function signal config ***", 1);
}


int	main(void) {
	ft_putstr("main server pid = ", getpid());
	ft_putstr("****** main start signal config ******", 1);
	signal_config();
	while (1) {
		ft_putstr("while_1", 1);
		pause();
		ft_putstr("while_2", 1);
	}
	ft_putstr("****** main end signal config ******", 1);
	return (0);
}
