#include "minitalk.h"

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
*/

void	init_signal_pid(void) {
	server.pid = 0;
	server.len = 0;
	server.flag = 0;
	server.message = NULL;
}

/*
void	send_message(struct sigaction sa) {
	while (*server.message) {
		send_one_byte(*server.message);
		server.message++;
	}
}
*/
/*
unsigned int	send_one_bit(bool bit) {	
}

void	send_one_byte(unsigned char *c) {

}
*/
void	send_len_of_message() {
	unsigned int	len;
	unsigned int	bit;

	len = 32;
	bit = 2147483648;
	while (len--) {
		if (server.len >= bit) {
			ft_kill(server.pid, SIGUSR1);
			server.flag = 1;
			server.len -= bit;
		}
		else {
			ft_kill(server.pid, SIGUSR2);
			server.flag = 2;
		}
		if (server.flag) {
			pause();
			bit /= 2;
		}
		else {
			len++;
		}
		if (!len) {
			ft_putstr("line hase ben send successefly", server.flag);
			init_signal_pid();
			exit(EXIT_SUCCESS);
		}
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context) {
	(void)context;
	if (server.flag && info->si_pid == (int)server.pid && signum == SIGUSR1) {
		server.flag = 1;
	}
	else if (server.flag && info->si_pid == (int)server.pid && signum == SIGUSR2) {
		server.flag = 2;
	}
	else {
		server.flag = 0;
	}
}

// 23 line
void	check_args(int argc, char **argv) {
	if (argc == 3) {
		server.pid = ft_atoi(argv[1]);
		if (server.pid < 2 || !*argv[2]) {
			if (!*argv[2]) {
				ft_putstr("error: Empty message", 1);
			}
			if (server.pid < 2) {
				ft_putstr("error: Invalid process ID", 1);
			}
			exit (EXIT_FAILURE);
		}
		else {
			ft_putstr("Client pid", getpid());
			ft_putstr("Server pid", server.pid);
			server.len = ft_strlen(argv[2]);
			server.message = argv[2];
		}
	}
	else {
		ft_putstr("error: Invalid number of arguments", 1);
		exit (EXIT_FAILURE);
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

int	main(int argc, char **argv) {
	
	check_args(argc, argv);
	signal_configuration();
//
	ft_putstr("server pid = ", server.pid);
	ft_putstr("len of message = ", server.len);
	ft_putstr("*************", 1);
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
