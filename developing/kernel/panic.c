#include <kernel.h>
#include <uart.h>

void panic(const char *str) {
    print(str);
    for (;;) ;
}
