#include "minitalk.h"
//	int	pid;
//	int	size;
//	int	flag;
//	int	error;
//	char	*message;

void	resive_size_off_message(int signum, info_signal *client) {
	if (!client->error) {
		if (signum == SIGUSR1) {
			client->size |= (1 << (32 - client->flag));
		}
		ft_kill(client->pid, SIGUSR1);
	}
	else {
		client->flag--;
		client->error = 0;
	}
}

void	initialise_variables(info_signal *client, int pid) {
	if (!client->pid) {
		client->pid = pid;
	}
	if (client->pid == pid) {
		client->flag++;
	}
/*	else {
		client->error++;
		ft_putstr("client->error", client->error);
	}
*/
}

void	signal_handler(int signum, siginfo_t *info, void *context) {
	static info_signal	client;

	(void)context;
	initialise_variables(&client, info->si_pid);
/*	if (client.flag == 1) {
		ft_kill(client.pid, SIGUSR1);
	}*/
	if (client.flag <= 32) {
		ft_putstr("client.flag", client.flag);
		resive_size_off_message(signum, &client);
	}
	if (client.flag == 32) {
		ft_putstr("client.message.size", client.size);
		client.pid = 0;
		client.size = 0;
		client.flag = 0;
		client.error = 0;
	}
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
	ft_putstr("srver process ID", getpid());
	signal_configuration();
	while (1) {
		pause();
	}
	return (EXIT_SUCCESS);
}
