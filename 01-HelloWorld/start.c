#define UART0 0x10000000L   // UART's address

#define THR 0     // Receive Holding Register

#define REG(r) ((volatile unsigned char *) (UART0 + r))
#define w_reg(r, v) (*(REG(r)) = (v))

int putchar(int c) {
    w_reg(THR, c);
    return c;
}

void print(const char *s) {
    while (*s) {
        putchar((int) *s);
        s++;
    }
}

void start() {
    print("Hello world\n");
    for ( ; ;) ;
}
