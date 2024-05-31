#include "minitalk.h"
//	int	pid;
//	int	size;
//	int	flag;
//	int	error;
//	char	*message;

void	save_message(int signum, info_signal *client) {
	static unsigned char	c;
	static int		z;
	static int		len;

	ft_putstr("send message", 1);
	//z++;
	if (signum == SIGUSR1) {
		c = (z << 1 | 1);
	ft_putstr("SIGUSR1", 1);
	}
	if (z == 8) {
		client->message[len++] = c;
		ft_putstr("************ ", 0);
		ft_putchar(c);
		ft_putstr(" ************ ", 1);
		c = 0;
		z = 0;
	}
	z++;
	ft_kill(client->pid, SIGUSR1);
}

void	resive_size_off_message(int signum, info_signal *client) {
	if (!client->error) {
		if (signum == SIGUSR1) {
			client->size |= (1 << (32 - client->flag));
		}

		ft_kill(client->pid, SIGUSR1);
	}
/*	else {
		client->flag--;
		client->error--;
	}
	*/
}

void	initialise_variables(info_signal *client, int signum, int pid) {
	if (client->pid == pid) {
		client->flag++;
	}
	else if (!client->pid && signum == SIGUSR1) {	// for the fisrt signal recived by client
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
	initialise_variables(&client, signum, info->si_pid);
	if (client.flag && client.flag <= 32) {
		ft_putstr("client.flag", client.flag);
		resive_size_off_message(signum, &client);
	}
/*	if (client.flag == 33) {
		ft_kill(client.pid, SIGUSR2);
		ft_putstr("client.message.size", client.size);
		client.pid = 0;
		client.size = 0;
		client.flag = 0;
//		client->message = (char*)malloc(sizeof(char) * (client.size + 1)); // allocate the size of 
	}
*/	else if (client.flag >= 33 && client.flag <= ((client.size * 8) + 33)) {
		
		ft_putstr("client.message.size", client.size);
		if (client.flag == 33) {
			client.message = (char*)malloc(sizeof(char) * (client.size + 1)); // allocate the size of 
			client.message[client.size] = 0;;
			if (!client.flag) {
			//initalaize varibel
			//set new pid
			}
		}
		save_message(signum, &client);
//		ft_putstr("client.message.size", client.size);
	}
	if (client.flag == ((client.size * 8) + 32)) {
		ft_putstr("*** messahe = ", 0);
		ft_putstr(client.message, 0);
		ft_putstr(" ***", 1);
		free(client.message);
		client.message = NULL;
		client.pid = 0;
		client.size = 0;
		client.flag = 0;
		client.error = 0;

	}
//	else if
	/*}
	if (client.flag == ((client.size * 8) + 32)) {
*/	/*else if {
		ft_putstr("client.message.pid", client.pid);
		ft_putstr("client.message.size", client.size);
		ft_putstr("client.message.flag", client.flag);
		ft_putstr(client.message, 1);
		client.pid = 0;
		client.size = 0;
		client.flag = 0;
		client.error = 0;
	}*/
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
