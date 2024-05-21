// client.c
/*
unsigned int	ft_strlen(char *str){}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t server_pid = atoi(argv[1]);
	

    // Send SIGUSR1 to the server
    if (kill(server_pid, SIGUSR1) == -1) {
        perror("Error sending SIGUSR1");
        exit(EXIT_FAILURE);
    }
    sleep(1); // Wait a moment to ensure the signal is handled

    // Send SIGUSR2 to the server
    if (kill(server_pid, SIGUSR2) == -1) {
        perror("Error sending SIGUSR2");
        exit(EXIT_FAILURE);
    }
    sleep(1); // Wait a moment to ensure the signal is handled

    return 0;
}
*/
#include "nimitalk.h"

int	send_signal(char *str, pid_t pid) {
	char	*byt;
	int		z;

	byt = malloc(9);
	if (!byt) {
		return (0);
	}
	byt[8] = 0;
	while (*str) {
		convert_string_byts(&byt, *str);
		z = 0;
		while (byt[z]) {
			if (byt[z] == 48) {
				kill(pid, SIGUSR2);
			}
			else {
				kill(pid, SIGUSR1);
			}
			z++;
		}
		str++;
	}
}

int	main(int argc, char **argv) {
	unsigned int	str_len;
	pid_t 			pid;

	if (argc == 3) {
		pid = ft_atoi[1];
		str_len = ft_strlen(argv[2]);
		send_signal(argv[2], pid);
		/*kill(pid, SIGUSR2);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR1);*/
	}
	else {
		ft_putstr("error number of arguments\n");
	}
    return 0;
}
