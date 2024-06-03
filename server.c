#include "minitalk.h"

void	initialize_struct(info_signal *client) {
	client->size = 0;
	client->error = 0;
	client->pid = 0;
	client->flag = 0;
	if (client->message) {
		free(client->message);
		client->message = NULL;
		ft_putstr("free space hase acllocate", 1);
	}
	ft_putstr("clear struct", 1);
}

void receive_message(info_signal *client, int signum) {
    static unsigned char c = 0;
    static int bit = 7;
    static unsigned int index = 0;

    // When we receive the first bit, ensure we reset the index and character
    if (client->flag == 33) {
        index = 0;
        c = 0;
        bit = 7;
    }
    if (signum == SIGUSR1) {
        c |= (1 << bit);
    }
    bit--;

    if (bit < 0) {
        client->message[index++] = c;
        if (index == client->size) {        // end of message
            client->message[index] = '\0';  // null-terminate the message
           // ft_kill(client->pid, SIGUSR2);  // Send completion signal
            return;  // Exit the function after finishing the message
        }
        c = 0;
        bit = 7;
    }
    usleep(200);
    ft_kill(client->pid, SIGUSR1);
}

void	receive_size_of_message(info_signal *client, int signum) {
	if (signum == SIGUSR1) {
		client->size |= (1 << (32 - client->flag));
	}
	if (client->flag == 32) {
		ft_putstr("allocate for save characher of message", client->size);
		client->message = (char*)malloc(sizeof(char) * (client->size + 1));
		if (!client->message) {
			ft_putstr("error: cant allocate these buffer", client->size);
			ft_kill(client->pid, SIGUSR2);
			initialize_struct(client);
			exit(EXIT_FAILURE);
		}
	}
	usleep(200);
	ft_kill(client->pid, SIGUSR1);
}

void	check_processID(info_signal *client, int pid, int signum) {
	if (client->pid == pid) {	//	save recived bits in flag if pid == client->pid are conferm
		client->flag++;		//	client->flag == 32		//	size of message has bin send;
	}				//	client->flag == 32 + (size * 8) //	message has bin send;
	else if (!client->pid && signum == SIGUSR1) {	//	for comfirm client pid and save it to the struct;
		client->pid = pid;
		ft_putstr("client process ID", client->pid);
		usleep(200);
		ft_kill(client->pid, SIGUSR1);
	}
	else {
		client->error++;
		ft_kill(pid, SIGUSR2);
		ft_putstr("client->error", client->error);
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context) {
	static info_signal	client;

	(void)context;
	check_processID(&client, info->si_pid, signum);
	if (client.flag) {
		if (client.flag <= 32) {
			receive_size_of_message(&client, signum);
		}
		else if (client.flag > 32 && client.flag <= ((client.size * 8) + 32)) {
			receive_message(&client, signum);
		}
		if (client.flag == ((client.size * 8) + 32)) {
			ft_putstr(client.message, client.size);
			ft_putstr("******flag ", client.flag);
			ft_putstr("successefuly", 1);
			initialize_struct(&client);
		}
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
