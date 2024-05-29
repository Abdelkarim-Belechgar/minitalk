#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void ft_putstr(const char *prefix, unsigned int nbr) {
    printf("%s: %u\n", prefix, nbr);
}

void conver(bool bit, unsigned int *new_val, int len) {
    if (bit) {
        *new_val |= (1U << len); // Set the bit at position 'len'
    }
}

unsigned int send_bits(unsigned int nbr) {
    unsigned int bit;
    int len;
    unsigned int new_val = 0;

    len = 31; // Start from the highest bit (31st bit)
    bit = 1U << len; // Initialize bit to 2^31

    while (len >= 0) { // Loop through 32 bits
        if (nbr & bit) { // Check if the current bit in 'nbr' is set
            conver(true, &new_val, len);
        }
        bit >>= 1; // Move to the next lower bit
        len--;
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

