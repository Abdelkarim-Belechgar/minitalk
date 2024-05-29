#include "minitalk.h"

static int	flag;

void	signal_handler(int signum) {
	if (signum == SIGUSR1) {
		flag++;
	}
	/*else if (flag == 32 && signum == SIGUSR2) {
		flag = 0;
		ft_putstr("size of message has ben send successfuly", 1);
	}
	else if (flag == (size * 8) && signum == SIGUSR2) {
		ft_putstr("message has ben send successfuly", 1);
		exit(EXIT_SUCCESS);
	}
	else {
		ft_putstr("has not ben send", 1);
	}*/
}

void	send_size_of_message(int pid, int message_size) {
	unsigned int	decimal;
	int	hint;
	int	confirm;

	confirm = 1;
	decimal = 2147483648;
	while (32 > flag) {
		if ((unsigned int)message_size >= decimal) {
			ft_kill(pid, SIGUSR1);
			hint = 1;
		}
		else {
			ft_kill(pid, SIGUSR2);
			hint = 0;
		}
		pause();
		if (confirm == flag) {
			if (hint) {
				message_size -= decimal;
			}
			confirm++;
			decimal /= 2;
		}
		else {
			flag--;
		}
	}
	ft_putstr("flag", flag);
}

int	handle_arguments(int argc, char **argv, int *pid) {
	int	size;

	if (argc != 3)
	{
		ft_putstr("error: Invalid number of arguments", 1);
		exit (EXIT_FAILURE);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid < 2 || !*argv[2]) {
		if (!*argv[2]) {
			ft_putstr("error: Empty message", 1);
		}
		if (*pid < 2) {
			ft_putstr("error: Invalid process ID", 1);
		}
		exit (EXIT_FAILURE);
	}/*
	ft_kill(*pid, SIGUSR1);
	pause();*/
	size = ft_strlen(argv[2]);
	ft_putstr("Client pid", getpid());
	ft_putstr("Server pid", *pid);
	return (size);
}

int	main(int argc, char **argv) {
	int	message_size;
	int	pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	message_size = handle_arguments(argc, argv, &pid);
	ft_putstr("message_size", message_size);
	send_size_of_message(pid, message_size);
	ft_putstr("final", 1);
	return (EXIT_SUCCESS);
}
