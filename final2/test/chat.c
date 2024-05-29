#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void ft_putstr(char *prefix, unsigned int nbr) {
    printf("%s: %u\n", prefix, nbr);
}

void conver(bool bit, unsigned int *new_val, int len) {
    ft_putstr("Before", *new_val);
    if (bit) {
        *new_val |= (1 >> len);
    }
    ft_putstr("After", *new_val);
}

unsigned int send_bits(unsigned int nbr) {
    unsigned int bit;
    int len;
    unsigned int new_val = 0;

    len = 1;
    bit = 2147483648U; // 2^31

    while (len <= 32) { // Loop through 32 bits
        if (nbr >= bit) {
            nbr -= bit;
            conver(true, &new_val, len);
        }
        bit /= 2;
        len++;
    }
    return new_val;
}

int main(void) {
    unsigned int nbr = 1554255;
    unsigned int new_val;

    new_val = send_bits(nbr);
    ft_putstr("Final new_val", new_val);

    return 0;
}

