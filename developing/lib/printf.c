#include <stdarg.h>
#include <types.h>
#include <uart.h>

char digits[] = "0123456789ABCDEF";

void printnum(int n, int base) {
    char buf[128];
    int i, neg;
    uint64 x;

    neg = 0;
    if (n < 0) {
        x = -n;
        neg = 1;
    } else {
        x = n;
    }
    i = 0;
    do {
        buf[i++] = digits[x % base];
    } while ((x /= base) != 0);
    if (neg) {
        buf[i++] = '-';
    }
    while (--i >= 0) {
        putchar(buf[i]);
    }
}

void printptr(uint64 n) {
    int i;

    putchar('0');
    putchar('x');
    for (i = 0; i < (int) sizeof(uint64) * 2; i++, n <<= 4) {
        putchar(digits[n >> (sizeof(uint64) * 8 - 4)]);
    }
}

void printf(const char *fmt, ...) {
    va_list ap;
    int i, state, c;
    char *s;

    va_start(ap, fmt);
    state = 0;
    for (i = 0; fmt[i]; i++) {
        c = fmt[i] & 0xff;
        if (state == 0) {
            if (c == '%') {
                state = '%';
            } else {
                putchar(c);
            }
        } else if (state == '%') {
            if (c == 'd') {
                printnum(va_arg(ap, int), 10);
            } else if (c == 'l') {
                printnum(va_arg(ap, int64), 10);
            } else if (c == 'x') {
                printnum(va_arg(ap, int), 16);
            } else if (c == 'p') {
                printptr(va_arg(ap, uint64));
            } else if (c == 's') {
                s = va_arg(ap, char *);
                if (s == 0) s = "(null)";
                while (*s != 0) {
                    putchar(*s);
                    s++;
                }
            } else if (c == 'c') {
                putchar(va_arg(ap, int));
            } else if (c == '%') {
                putchar(c);
            } else {
                putchar('%');
                putchar(c);
            }
            state = 0;
        }
    }
}
