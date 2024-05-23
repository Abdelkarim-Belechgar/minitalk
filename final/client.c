#include "minitalk.h"
/*
void	handling_args(int argc, char **argv) {
	unsigned int	pid;

	if (argc == 3) {
		if ((pid = ft_atoi(argv[1])) < 2 ) {
			ft_putstr("pid error");
			exit (1);
		}
		if (!*argv[2]) {
			ft_putstr("empty message");
			exit(1);
		}
	}
	else {
		ft_putstr("error number of arguments");
		exit(1);
	}
}
*/
void	init_signal_pid(i_signal *node) {
	node->si_pid = 1;
	node->len = 1;
	node->message = NULL;
}

#include <stdio.h>
int	main(int argc, char **argv) {
	static i_signal	server;

	(void)argc;
	(void)argv;
	printf("si_pid = %d\n", server.si_pid);
	printf("len = %d\n", server.len);
	printf("message = %s\n", server.message);
	init_signal_pid(&server);
	printf("*************\n");
	printf("si_pid = %d\n", server.si_pid);
	printf("len = %d\n", server.len);
	printf("message = %s\n", server.message);
	return (0);
}
