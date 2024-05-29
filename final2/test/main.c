#include <unistd.h>
#include <stdbool.h>
void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(unsigned int nbr) {
	if (nbr > 9) {
		ft_putnbr(nbr / 10);
	}
	nbr %= 10;
	nbr += 48;
	ft_putchar(nbr);
}

void	ft_putstr(char *str, unsigned int nbr) {
	while (*str) {
		ft_putchar(*str);
		str++;
	}
	if (nbr > 1) {
		ft_putstr(" = ", 0);
		ft_putnbr(nbr);
	}
	if (nbr) {
		ft_putchar('\n');
	}
}
void	convert_bits_to_int(bool flag) {
	static unsigned int	len;
	static unsigned int	bit;
	static int		z;

	if (!z && !bit) {
		ft_putstr("0b", 0);
		bit = 2147483648;
		z++;
	}
	if (z <= 32) {
		if (flag) {
			ft_putstr("1", 0);
			len += bit;
		}
		else {
			ft_putstr("0", 0);
		}
		bit /= 2;
		z++;
	}
	if (z == 33) {
		ft_putchar('\n');
		ft_putstr("size *", len);
	}
	
}
unsigned int	send_bits(unsigned int nbr) {
	unsigned int	bit;
//	unsigned int	len;
	unsigned int	new;

	//len = 0;
	new = 0;
	bit = 2147483648;
	while (new < 32) {
		if (nbr >= bit) {
			convert_bits_to_int(true);
			nbr -= bit;
	//		len |= (1 << new);
		}
		else {
			convert_bits_to_int(false);
		}
	//	ft_putstr("len", len);
		bit /= 2;
		new++;
	}
	return (new);
}

int	main(void) {
	int	nbr = 1554255;
	int	new;
	ft_putstr("0b", 1);
	new = send_bits(nbr);
	ft_putchar('\n');
	ft_putstr("new", new);
	return (0);
}
