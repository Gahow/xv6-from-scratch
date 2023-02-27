#include <kernel.h>
#include <printf.h>
#include <uart.h>

void panic(const char *str) {
    printf(str);
    for (;;) ;
}
