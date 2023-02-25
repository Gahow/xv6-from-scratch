#include <types.h>
#include <uart.h>

void *memset(void *s, int c, int n) {
    int i;
    char *cs;

    cs = (char *) s;
    for (i = 0; i < n; i++) {
        *(cs + i) = c;
    }
    return s;
}

/* char *to_string(uint64 n) {
    char buf[512];
    int i;

    i = 0;
    do {
        buf[i++] = n % 10 + '0';
    } while ((n /= 10) != 0);
    buf[i++] = '\0';
    reverse(buf);
    return buf;
} */

void reverse(char *str) {
    int n;
    int i, j;

    n = 0;
    while (*(str + n)) {
        n++;
    }
    for (i = 0, j = n - 1; i < j; i++, j--) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}
