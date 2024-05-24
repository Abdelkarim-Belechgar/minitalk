#include "minitalk.h"
#include <stdio.h>

static i_signal	server;
// SIGUSR2	= 2;
// SIGUSR1	= 1;

/*
unsigned int	convert_decimal_to_binary(char *str, unsigned char c) {
	unsigned int	byte;
	unsigned int	res;
	unsigned int	z;

	z = 8;
	res = 0;
	byte = 128;
	initialisation_string(str);
	while (z--) {
		if (c >= byte) {
			res++;
			*str = '1';
			c -= byte;
		}
		byte /= 2;
		str++;
	}
}

unsigned int	send_one_bit(bool bit) {
	
}


void	send_one_byte(char *c) {
	int	
}

void	init_signal_pid(i_signal *node) {
	node->si_pid = 1;
	node->len = 1;
	node->message = NULL;
}
*/
void	handler_signal(int signum, siginfo_t *info, void *context) {
//	signum -= SIGUSR1; //if (signum) --> means SIGUSR2 else if (!signum) ---> means SIGUSR1
	(void)info;
	(void)context;
	if ((server.flag == 1 && signum == SIGUSR1) || (server.flag == 2 && signum == SIGUSR2)) {
		server.flag = 0;
	}
}
/*
void	send_message(struct sigaction sa) {
	while (*server.message) {
		send_one_byte(*server.message);
		server.message++;
	}
}
*/
void	send_len_of_message() {
	unsigned int	len;
	unsigned int	bit;

	len = 32;
	bit = 2147483648;
	printf("lennn = %d\n", server.len);
	while (len--) {
		if (server.len >= bit) {
			if (kill(server.si_pid, SIGUSR1) == -1) {
				server.flag = 0;
				ft_putstr("error: failed requist send SIGUSR1", 1);
			}
			else {
				//ft_putstr("confirm requist SIGUSR1", 1);
				ft_putchar('1');
				server.flag = 1;
				server.len -= bit;
			}
		}
		else {
			if (kill(server.si_pid, SIGUSR2) == -1) {
				server.flag = 0;
				ft_putstr("error: failed requist send SIGUSR2", 1);
			}
			else {
				//ft_putstr("confirm requist SIGUSR2", 1);
				ft_putchar('0');
				server.flag = 2;
			}
		}
		if (server.flag) {
			bit /= 2;
		}
		else {
			len++;
		}
	//	pause();
	}
}

// 24 line
void	handling_args(int argc, char **argv) {
	if (argc == 3) {
		server.si_pid = ft_atoi(argv[1]);
		if (server.si_pid < 2 || !*argv[2]) {
			if (!*argv[2]) {
				ft_putstr("error: empty message", 1);
			}
			if (server.si_pid < 2) {
				ft_putstr("error: pid error", 1);
			}
			exit (EXIT_FAILURE);
		}
		else {
			server.len = ft_strlen(argv[2]);
			server.message = argv[2];
			ft_putstr("Server pid", server.si_pid);
			ft_putstr("Client pid", getpid());
		}
	}
	else {
		ft_putstr("error: number of arguments", 1);
		exit (EXIT_FAILURE);
	}
}

void	configure_received_signal(void) {
	struct sigaction	sa;

	sa.sa_sigaction = &handler_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		ft_putstr("error: in catching SIGUSR1", 1);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1) {
		ft_putstr("error: in catching SIGUSR2", 1);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv) {
	handling_args(argc, argv);
	configure_received_signal();
//
	printf("si_pid = %d\n", server.si_pid);
	printf("len = %d\n", server.len);
	printf("message = %s\n", server.message);
	printf("*************\n");
	send_len_of_message();
	//send_message();	
	/*
	init_signal_pid(&server);
	printf("si_pid = %d\n", server.si_pid);
	printf("len = %d\n", server.len);
	printf("message = %s\n", server.message);
	*/
	return (EXIT_SUCCESS);
}
