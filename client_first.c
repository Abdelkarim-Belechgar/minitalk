#include <unistd.h>
#include <stdlib.h>
pid_t	pid_m;
int		pid_n;

pid_m = getpid();
pid_n = getpid();

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;


	sign = 1;
	result = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - 48;
		str++;
	}
	return (sign * result);
}

#include <stdio.h>
int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("%d\n", pid_m);
	printf("%d\n", pid_n);
	
	printf("%d\n", ft_atoi("    - 5444"));
	return (0);
}
