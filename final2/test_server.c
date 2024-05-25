#include "minitalk.h"

static i_signal	client;

void	initalaize_varibles(unsigned int send_pid) {
	if (!client.flag) {
		client.flag = 32;
	}
	if (!client.pid) {
		client.pid = send_pid;
	}
	if (client.pid != send_pid) {
		ft_putstr("Warning: server received a signal from process ID", send_pid);
		ft_putstr("before completing communication with process ID", client.pid);
		ft_putstr("Signals are ignored.", 1);
	}
}

void	signal_handler(int signum, siginfo_t *info, void *notg)
{
//	ft_putstr("--- start function handeler_message ---", 1);
//	ft_putstr("client pid = ", client.pid);
//	ft_putstr("client len = ", client.len);
//	ft_putstr("client flag = ", client.flag);
	(void)notg;
	initalaize_varibles((unsigned int)info->si_pid);
	if ((int)client.pid == info->si_pid) {
		client.flag--;
		if (signum == SIGUSR1) {
			ft_putchar('1');
			client.len |= (1 << client.flag);
			ft_kill(info->si_pid, SIGUSR1);
		}
		else {
			ft_putchar('0');
			ft_kill(info->si_pid, SIGUSR2);
		}
		if (!client.flag) {
			client.pid = 0;
		}
	}
	if (client.flag == 0) {
		ft_putstr("size of len send succussfuly ", client.len);
		client.len = 0;
	}
//	ft_putstr("--- end function handeler_message ---", 1);
}

void	signal_configuration(void) {
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		ft_putstr("error: sigaction()=Failed to change the action from SIGUSR1", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1) {
		ft_putstr("error: sigaction()=Failed to change the action from SIGUSR2", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(void) {
	ft_putstr("main server pid = ", getpid());
	ft_putstr("****** main start signal config ******", 1);
	signal_configuration();
	while (1) {
//		ft_putstr("start while --> pause()", 1);
		pause();
//		ft_putstr("end while --> pause()", 1);
	}
	ft_putstr("****** main end signal config ******", 1);
	return (0);
}
