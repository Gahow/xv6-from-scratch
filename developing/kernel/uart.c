#include <types.h>
#include <uart.h>

int putchar(int c) {
    w_reg(RHR, c);
    return c;
}

void print(const char *s) {
    while (*s) {
        putchar((int) *s);
        s++;
    }
}
