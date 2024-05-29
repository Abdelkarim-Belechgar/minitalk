#include <stdio.h>

typedef struct k
{
    unsigned int    bit;
    unsigned int    len;
}               t_list;


void    server_bit(t_list *head, int flag, int bit) {
    if (flag) {
        head->len |= (1 << bit);
    }
}

void    client_bit(t_list *head) {
    int    c;
    int     z;

    z = 32;
    c = 455777;
    head->bit = 2147483648;
    printf("server = 0b");
    while (z--) {
        if (c >= head->bit) {
            c -= head->bit;
            server_bit(head, 1, z);
            printf("1");
        }
        else {
            server_bit(head, 0, 0);
            printf("0");
        }
        head->bit /= 2;
    }
    printf("\n");
}

int main(void) {
    static t_list   new;
    client_bit(&new);
    printf("server = %d", new.len);
}
