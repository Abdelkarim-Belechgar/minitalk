#include "minitalk.h"

static unsigned int	flag;

void	signal_handler(int signum) {
	if (signum == SIGUSR1) {
		flag++;
	}
	else if (signum == SIGUSR2) {
		ft_putstr("error:  These processes have been killed by the server.", 1);
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
		usleep(300);
	}
}

void	send_message(int pid, unsigned char *message) {
	ft_putstr("start sent message", 1);
	while (*message) {
		usleep(1000);
		send_one_byte(pid, *message);
		message++;
	}
}

void	send_size_off_message(int pid, unsigned int message_size) {
	unsigned int	decimal;
	bool		bit;

	decimal = 2147483648;
	ft_putstr("start sent size off message", 1);
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
		ft_putstr("error:  number of arguments not valid", 1);
		exit (EXIT_FAILURE);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid < 2 || !*argv[2]) {
		if (!*argv[2]) {
			ft_putstr("error:  Empty message", 1);
		}
		if (*pid < 2) {
			ft_putstr("error:  process ID is not a valid", 1);
		}
		exit (EXIT_FAILURE);
	}
	send_one_bit(*pid, true);
	pause();
	size = ft_strlen(argv[2]);
	return (size);
}

int	main(int argc, char **argv) {
	unsigned int	message_size;
	int		pid;

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	message_size = handle_arguments(argc, argv, &pid);
	ft_putstr("client process ID", getpid());
	ft_putstr("message size", message_size);
	send_size_off_message(pid, message_size);
	send_message(pid, (unsigned char*)argv[2]);
	ft_putstr("message has been sent successfully", 1);
	return (EXIT_SUCCESS);
}
