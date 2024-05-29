#include "minitalk.h"
//	SIGUSR2 = 2;	// 0 bit
//	SIGUSR1 = 1;	// 1 bit

static int	pid;
//	server.pid = 0;
//	server.len = 0;
//	server.flag = 0;
//	server.message = NULL;
/*
void	send_one_byte(unsigned char c) {
	unsigned int	len;
	unsigned int	decimal;

	len = 8;
	decimal = 128;
	server.len = ft_strlen(argv[2]);
	while (len--) {
		server.flag = 0;
		if (c >= decimal) {
			ft_putchar('1');
			send_one_bit(server.pid, true);
		}
		else {
			ft_putchar('0');
			send_one_bit(server.pid, false);
		}
		pause();
		if (server.flag) {
			if (server.flag == 1) {
				c -= decimal;
			}
			decimal /= 2;
		}
		else {
			len++;
		}
	}
}
*/
void	send_len_of_message(int len) {
	int	decimal;
	int	hint;
	int	flag;
	int	new_pid;

	flag = 0;
	decimal = 2147483648;
	while (flag < 32) {
		new_pid = pid;
		hint = 0;
		if (len >= decimal) {
			ft_kill(pid, SIGUSR1);
			hint++;
		}
		else {
			ft_kill(pid, SIGUSR2);
		}
		pause();
		if (pid) {
			if (hint) {
				len -= decimal;
			}
			decimal /= 2;
			ft_putstr("decimal", decimal);
		}
		else {
			flag--;
		}
		pid = new_pid;
		flag++;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *context) {
	static int	flag;
	
	(void)context;
	if (pid == info->si_pid && signum == SIGUSR2) {
//		ft_kill(info->si_pid);
		exit(EXIT_SUCCESS);
	}
	if (pid == info->si_pid && signum == SIGUSR1) {
		flag++;
		pid = flag;
	}
	else {
		ft_putstr("bad trip", 1);
		pid = 0;
	}
	ft_putstr("handl falg", flag);
}

// finsh
void	check_args(int argc, char **argv, int *len) {
	if (argc != 3) {
		ft_putstr("error: Invalid number of arguments", 1);
		exit (EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 2 || !*argv[2]) {
		if (!*argv[2]) {
			ft_putstr("error: Empty message", 1);
		}
		if (pid < 2) {
			ft_putstr("error: Invalid process ID", 1);
		}
		exit (EXIT_FAILURE);
	}
	else {
		*len = ft_strlen(argv[2]);
		ft_putstr("Client pid", getpid());
		ft_putstr("Server pid", pid);
		ft_putstr("message len",*len);
	}
}

// finsh
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
	int	len;
	
	check_args(argc, argv, &len);
	signal_configuration();
	send_len_of_message(len);
	
	//send_message();	
	/*
	init_signal_pid(&server);
	printf("si_pid = %d\n", server.si_pid);
	printf("len = %d\n", server.len);
	printf("message = %s\n", server.message);
	*/
	return (EXIT_SUCCESS);
}
