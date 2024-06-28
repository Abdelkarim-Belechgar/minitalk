#include "minitalk.h"

void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		ft_putstr("process hase ben blaked", 1);
		exit(EXIT_FAILURE);
	}
}

void	send_one_byte(int pid, char message)
{
	unsigned char	decimal;
	size_t			z;
	bool			bit;

	z = 8;
	decimal = 128;
	while (z--)
	{
		if (message >= decimal)
		{
			message -= decimal;
			bit = 1;
		}
		else
			bit = 0;
		decimal /= 2;
		send_one_bit(pid, bit, 1);
		usleep(200);
	}
}

void	send_message(int pid, char *message)
{
	while (*message)
	{
		send_one_byte(pid, *message);
		message++;
	}
}

void	send_size_off_message(int pid, size_t message_size)
{
	size_t	decimal;
	size_t	flag;
	bool	bit;

	flag = 32;
	decimal = 2147483648;
	while (flag--)
	{
		if (message_size >= decimal)
		{
			message_size -= decimal;
			bit = 1;
		}
		else
			bit = 0;
		decimal /= 2;
		send_one_bit(pid, bit, 1);
		usleep(200);
	}
}

size_t	handle_arguments(int argc, char **argv, int *pid)
{
	size_t	size;

	if (argc != 3)
	{
		ft_putstr("Error:  Number of arguments not valid", 1);
		exit (EXIT_FAILURE);
	}
	*pid = ft_atoi(argv[1]);
	if (*pid < 2 || !*argv[2])
	{
		if (!*argv[2])
			ft_putstr("Error:  Empty message", 1);
		if (*pid < 2)
			ft_putstr("Error:  Process ID is not a valid", 1);
		exit(EXIT_FAILURE);
	}
	send_one_bit(*pid, 1, 1);
	usleep(50);
	size = ft_strlen(argv[2]);
	return (size);
}

int	main(int argc, char **argv)
{
	size_t	message_size;
	int		pid;

	ft_putstr("client.pid", getpid());
	signal(SIGUSR2, signal_handler);
	message_size = handle_arguments(argc, argv, &pid);
	send_size_off_message(pid, message_size);
	send_message(pid, argv[2]);
	return (EXIT_SUCCESS);
}
