#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	handler_msg(int sig_msg, siginfo_t *info, void *notg)
{
	static char		chr = 0;
	static int		client_pid;
	static int		last_pid;
	static int		cnt = 7;

	(void)notg;
	client_pid = info->si_pid;
	printf("start function handeler_message\n");
	if (client_pid != last_pid)
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
		printf("*****message = ");
		write(1, &chr, 1);
		printf("*****\n");
		chr = 0;
		cnt = 7;
	}
	printf("end function handeler_message\n\n");
}

void	signal_config(void)
{
	struct sigaction	action;

	printf("start function signal config\n");
	action.sa_sigaction = &handler_msg;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR2, &action, 0) == -1)
		write(1, "Error\n", 6);
	if (sigaction(SIGUSR1, &action, 0) == -1)
		write(1, "Error SIGUSR2\n", 6);
	printf("end function signal config\n\n");
}


int	main(void) {
	printf("main server pid = %d\n", getpid());
	printf("****main start signal config*****\n");
	signal_config();
	while (1) {
		printf("while_1\n");
		pause();
		printf("while_2\n");
	}
	printf("****main end signal config*****\n");
	return (0);
}
