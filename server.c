#include "minitalk.h"

//-------------------------------------------------------
//	typedef struct	t_signal {
//		int		pid;
//		int		new_pid;
//		unsigned int	size;
//		unsigned int	new_size;
//		unsigned int	flag;
//		unsigned int	new_flag;
//		unsigned int	error;
//	} 		info_signal;
//------------------------------------------------------
void	initialize_struct(info_signal *client) {
	client->pid = 0;
	client->new_pid = 0;
	client->size = 0;
	client->new_size = 0;
	client->flag = 0;
	client->new_flag = 0;
	client->error = 0;
	client->message = 0;
	client->bit = 0;
}

void	receive_message(info_signal *client, int signum) {
	if (client->flag == 33) {
		ft_putchar('\n');
	}
	if (signum == SIGUSR1) {
		client->message |= (1 << (7 - client->bit));
	}
	client->bit++;
	if (client->bit == 8) {
		ft_putchar(client->message);
		client->bit = 0;
		client->message = 0;
	}
}

void	receive_size_of_message(info_signal *client, int signum, bool bit) {
	if (bit && signum == SIGUSR1) {
		client->size |= (1 << (32 - client->flag));

	}
	else if (!bit && signum == SIGUSR1) {
		client->new_size |= (1 << (32 - client->new_flag));
	}
}

void	check_processID(info_signal *client, int pid, int signum) {
	static unsigned int	tmp_flag;
	static unsigned int	tmp_size;
	int		tmp_pid;
	

	if (client->pid == pid) {
		client->flag++;
		client->error = 0;
	}
	else if (!client->pid && signum == SIGUSR1) {
		client->pid = pid;
		tmp_flag = client->flag;
	}
	else if (client->new_pid == pid) {
		client->new_flag++;
		client->error++;
		if (client->flag > tmp_flag || client->new_flag == 32) {
			if (client->flag > tmp_flag) {
				ft_kill(client->pid, SIGUSR2);
			}
			else {
				client->flag = 32;
			}
			tmp_size = client->new_size;
			tmp_pid = client->new_pid;
			initialize_struct(client);
			client->pid = tmp_pid;
			client->size = tmp_size;
		}
	}
	else {
		client->error++;
		client->new_flag = 0;
		tmp_flag = client->flag;
		client->new_pid = pid;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *conetxt) {
	static info_signal	client;

	(void)conetxt;
	check_processID(&client, info->si_pid, signum);
	if (!client.error) {
		if (client.flag <= 32) {
			if (client.flag) {
				receive_size_of_message(&client, signum, true);
			}
			send_one_bit(client.pid, true);
		}
		else if (client.flag > 32) {
			receive_message(&client, signum);
		}
		if (client.flag == (32 + (client.size * 8))) {
			ft_putstr("\nmessage message has ben received successefuly from client PID", client.size);
			initialize_struct(&client);
		}
	}
	else {
		if (client.new_flag <= 32) {
			if (client.new_flag) {
				receive_size_of_message(&client, signum, false);
			}
			send_one_bit(client.new_pid, true);
		}
	}
}

int	main(void) {
	struct sigaction	sa;

	ft_putstr("server process ID", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)) {
		ft_putstr("error: sigaction()=Failed to change the action", 1);
		exit(EXIT_FAILURE);
	}
	while (1) {
		pause();
	}
}
