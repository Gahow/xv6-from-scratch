#include <uart.h>

void main() {
    int c;

    uartinit();
    print("Hello world!\n");
    while (1) {
        c = getchar();
        if (c != -1) {
            switch (c) {
                case 8: case 127:
                    print("\b \b");
                    break;
                case 10: case 13:
                    print("\n");
                    break;
                default:
                    putchar(c);
            }
        }
    }
}
