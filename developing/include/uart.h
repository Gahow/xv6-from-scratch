#ifndef UART_H
#define UART_H

#define UART0 0x10000000L   // UART's address

#define THR 0       // Transmit Holding Register
#define RHR 0       // Receive Holding Register
#define IER 1       // Interrupt Enable Register
#define FCR 2       // FIFO Control Register
#define LCR 3       // Line Control Register
#define LSR 5       // Line Status Register
#define DLL 0       // divisor latch least
#define DLM 1       // divisor latch most

#define LCR_DIVISOR_LATCH   (1 << 7)    // bit for divisor latch enable
#define LCR_WORD_LENGTH     (3 << 0)    // 0x03 represent word length 8
#define IER_RT_ENABLE       (3 << 0)    // enable receive / transmit interrupt
#define FCR_FIFO_ENABLE     (1 << 0)    // FIFO enable
#define FCR_FIFO_RESET      (3 << 1)    // receiver / transmit FIFO reset

#define REG(r)      ((volatile uint8 *) (UART0 + r))
#define r_reg(r)    (*(REG(r)))
#define w_reg(r, v) (*(REG(r)) = (v))

void    uartinit();
int     putchar(int c);
int     getchar();
void    print(const char *s);

#endif
