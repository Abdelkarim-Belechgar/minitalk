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
int	main(int argc, char **argv) {
	unsigned int	str_len;
	pid_t pid;

	if (argc == 3) {
		pid = ft_atoi[1];
		str_len = ft_strlen(argv[2]);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR1);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR2);
		kill(pid, SIGUSR1);
	}
	else {
		ft_putstr("error number of arguments\n");
	}
    return 0;
}
