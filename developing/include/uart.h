#ifndef UART_H
#define UART_H

#define UART0 0x10000000L   // UART's address

#define RHR 0       // Receive Holding Register
#define THR 0       // Transmit Holding Register

#define REG(r)      ((volatile uint8 *) (UART0 + r))
#define r_reg(r)    (*(REG(r)))
#define w_reg(r, v) (*(REG(r)) = (v))

int     putchar(int c);
void    print(const char *s);

#endif
