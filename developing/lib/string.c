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
