// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Handler for SIGUSR1
void handle_sigusr1(int sig) {
    printf("Server received SIGUSR1\n");
}

// Handler for SIGUSR2
void handle_sigusr2(int sig) {
    printf("Server received SIGUSR2\n");
}

int main() {
	int	z = 100;
    // Set up the SIGUSR1 handler
	while (z--) {
	if (signal(SIGUSR1, handle_sigusr1) == SIG_ERR) {
        perror("Cannot handle SIGUSR1");
        exit(EXIT_FAILURE);
    }

    // Set up the SIGUSR2 handler
    if (signal(SIGUSR2, handle_sigusr2) == SIG_ERR) {
        perror("Cannot handle SIGUSR2");
        exit(EXIT_FAILURE);
    }
	}
    printf("Server is running with PID: %d\n", getpid());

    // Loop indefinitely to keep the server running
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}


/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function
void handle_sigint(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    // Set up the signal handler
    signal(SIGINT, handle_sigint);

    // Infinite loop to keep the program running
    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}
*/
