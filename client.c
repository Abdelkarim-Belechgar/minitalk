#include "minitalk.h"

static unsigned int	flag;

void	signal_handler(int signum) {
	if (signum == SIGUSR1) {
		flag++;
	}
	else if (signum == SIGUSR2) {
		ft_putstr("error: server has kill you it comminicate to other process", 1);
		exit(EXIT_FAILURE);
	}
}

void	send_one_byte(int pid, unsigned char message) {
	unsigned char	decimal;
	int		z;
	bool		bit;

	z = 8;
	decimal = 128;
	while (z--) {
		if (message >= decimal) {
			message -= decimal;
			bit = 1;
		}
		else {
			bit = 0;
		}
		decimal /= 2;
		send_one_bit(pid, bit);
		usleep(500);
	}
}

void	send_message(int pid, unsigned char *message) {
	while (*message) {
		usleep(1500);
		send_one_byte(pid, *message);
		message++;
	}
}

void	send_size_off_message(int pid, unsigned int message_size) {
	unsigned int	decimal;
	bool		bit;

	decimal = 2147483648;
	ft_putstr("start send size off message", 1);
	while (flag && 32 >= flag) {
		if (message_size >= decimal) {
			message_size -= decimal;
			bit = 1;
		}
		else {
			bit = 0;
		}
		decimal /= 2;
		send_one_bit(pid, bit);
		pause();
	}
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
	return (size);
}

int	main(int argc, char **argv) {
	unsigned int	message_size;
	int		pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	message_size = handle_arguments(argc, argv, &pid);
	pause();
	ft_putstr("message size", message_size);
	send_size_off_message(pid, message_size);
	send_message(pid, (unsigned char*)argv[2]);
	return (EXIT_SUCCESS);
}
