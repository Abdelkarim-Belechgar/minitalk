#include "minitalk.h"

static unsigned int	flag;

void	signal_handler(int signum) {
	if (signum == SIGUSR1) {	// conferm signal are comfirm resived by server;
		flag++;
	}
	else if (signum == SIGUSR2) {	// confirm all signal are resived by server;
		ft_putstr("Wait one moment. The server has been contaminated by another process.", 1);
		exit (EXIT_FAILURE);
	}
}

void	send_message(int pid, unsigned char *message) {
	int	decimal;
	int	z;

	while (*message) {
		z = 8;
		decimal = 128;
		while (z--) {
			if (*message >= decimal) {
				*message -= decimal;
				ft_kill(pid, SIGUSR1);
			}
			else {
				ft_kill(pid, SIGUSR2);
			}
			decimal /= 2;
			pause();
		}
		ft_putchar((char)*message);
		ft_putstr("  = charachter has bin send successfuly", flag);
		message++;
	}
}

void	send_size_of_message(int pid, unsigned int message_size) {
	unsigned int	decimal;

	decimal = 2147483648;
	while (flag && 32 >= flag) {
		if (message_size >= decimal) {
			message_size -= decimal;
			ft_putchar('1');
			ft_kill(pid, SIGUSR1);
		}
		else {
			ft_putchar('0');
			ft_kill(pid, SIGUSR2);
		}
		decimal /= 2;
		pause();
	}
	ft_putchar('\n');
}

unsigned int	handle_arguments(int argc, char **argv, int *pid) {
	unsigned int	size;

	if (argc != 3) {
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
	}
	ft_kill(*pid, SIGUSR1);
	size = ft_strlen(argv[2]);
	ft_putstr("Server pid", *pid);
	ft_putstr("Client pid", getpid());
	return (size);
}

int	main(int argc, char **argv) {
	unsigned int	message_size;
	int		pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	message_size = handle_arguments(argc, argv, &pid);
	pause();
	send_size_of_message(pid, message_size);
	ft_putstr("size off message has ben send: message_size", message_size);
	send_message(pid, (unsigned char*)argv[2]);
	ft_putstr("message has ben send ", 1);
	return (EXIT_SUCCESS);
}
