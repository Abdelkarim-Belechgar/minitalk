#include "minitalk.h"

void	initialize_struct(info_signal *client) {
	client->size = 0;
	client->error = 0;
	client->pid = 0;
	client->flag = 0;
	if (client->message) {
		free(client->message);
		client->message = NULL;
	}
}

void	receive_message(info_signal *client, int signum) {
	static unsigned char	c;
	static int		bit;
	static unsigned int	index;

	bit--;
	if (client->flag == 33) {
		index = 0;
	}
	if (bit < 0) {
		bit = 7;
		c = 0;
	}
	if (signum == SIGUSR1) {
		ft_putchar('1');
		c |= (1 << bit);
	}
	else {
		ft_putchar('0');
	}
	if (!bit) {
		client->message[index++] = c;
		if (index == client->size) {		// end of message
			client->message[index] = '\0';	// null-terminate the message
		}
	}
	ft_kill(client->pid, SIGUSR1);

}

void	receive_size_of_message(info_signal *client, int signum) {
	if (signum == SIGUSR1) {
		client->size |= (1 << (32 - client->flag));
	}
	if (client->flag == 32) {
		ft_putstr("size of message", client->size);
		client->message = (char*)malloc(sizeof(char) * (client->size + 1));
		if (!client->message) {
			ft_putstr("error: cant allocate these buffer", client->size);
			initialize_struct(client);
			ft_kill(client->pid, SIGUSR2);
			exit(EXIT_FAILURE);
		}
	}
	ft_kill(client->pid, SIGUSR1);
}

void	check_processID(info_signal *client, int pid, int signum) {
	if (client->pid == pid) {	//	save recived bits in flag if pid == client->pid are conferm
		ft_putstr("handel", client->flag);
		client->flag++;		//	client->flag == 32		//	size of message has bin send;
	}				//	client->flag == 32 + (size * 8) //	message has bin send;
	else if (!client->pid && signum == SIGUSR1) {	//	for comfirm client pid and save it to the struct;
		client->pid = pid;
		ft_kill(client->pid, SIGUSR1);
	}
	else {
		client->error++;
		ft_putstr("client->error", client->error);
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context) {
	static info_signal	client;

	(void)context;
	check_processID(&client, info->si_pid, signum);
	if (!client.error && client.flag) {
		if (client.flag <= 32) {
			receive_size_of_message(&client, signum);
		}
		else if (client.flag > 32 && client.flag <= ((client.size * 8) + 32)) {
			receive_message(&client, signum);
		}
		if (client.flag == ((client.size * 8) + 32)) {
			ft_putstr("flag ", client.flag);
			ft_putstr(client.message, client.size);
			initialize_struct(&client);
			ft_kill(client.pid, SIGUSR2);
		}
	}
	else {
		initialize_struct(&client);
	
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
