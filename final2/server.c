#include "minitalk.h"

void	send_len_of_message(si_info *client, int signum) {
	static unsigned int	bit;

	if (!bit) {
		bit = 2147483648;
	}
	if (signum == SIGUSR1) {
		ft_putstr("SIGUSR1", 1);
		client->len += bit;
	}
	else {
		ft_putstr("SIGUSR0", 1);
	}
	bit /= 2;
	ft_kill(client->pid, SIGUSR1);
}

void	initalase_varibles(si_info *client, int new_pid) {
	static int	error;
	ft_putstr("start initalaze varible = ", 0);
	if (!client->pid) {
		ft_putstr("1", 1);
		error = 0;
		client->pid = new_pid;
	}
	if (client->pid == new_pid) {
		ft_putstr("2", 1);
		client->flag++;
		ft_putstr("client->flag", client->flag);
	}
	else {
		ft_putstr("3", 1);
		error++;
		client->error = error;
	}
	ft_putstr("end", 1);
}

void	signal_handler(int signum, siginfo_t *info, void *not) {
	static si_info	client;

	(void)not;
	client.error = 0;
	ft_putstr("client.flag", client.len);
	initalase_varibles(&client, info->si_pid);
//	ft_putstr("len = ", client.len);
	if (client.error) {
		//	egnore signal are resived from other prosses;
/*		if (client.error >= 15) {
			ft_putstr("Erorr: server are recived more tha 10 signal from other process", 1);
			ft_putstr("before completing communication with first \"Client process ID\"", client->old_pid);
			ft_putstr("server ", 1);
			exit(EXIT_FAILURE);
		}
*/		ft_putstr("Warning: server received a signal from process ID", info->si_pid);
		ft_putstr("before completing communication with process ID", (unsigned int)client.pid);
		ft_putstr("Signals are ignored.", 1);
	}
	else if (client.flag <= 32) {
		//ft_putstr("flag32", client.flag);
		//	resive size len of the message;
		send_len_of_message(&client, signum);
	}
	else if (client.flag == 33) {
		ft_putstr("flag33", client.flag);
		//	resive size len of the message;
		ft_kill(client.pid, SIGUSR2);
		ft_putstr("len", client.len);
		client.len = 0;
		client.pid = 0;
		client.flag = 0;
	}
	/*i
	else if (client.flag <= (33 + (client.len * 8))) {
		//	resive  message;
		send_message(&client, signum);
	}*/
	else {
		ft_putstr("flag34", client.flag);
		//	resive size len of the message;
		client.len = 0;
		client.pid = 0;
		client.flag = 0;
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
	ft_putstr("server process ID", getpid());
	signal_configuration();
	while (1) {
		pause();
	}
	return (0);
}
