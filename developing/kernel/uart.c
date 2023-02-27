#include <types.h>
#include <string.h>
#include <kernel.h>
#include <memlayout.h>
#include <uart.h>

void uartinit() {
    // disable all interrupt
    w_reg(IER, 0x00);

    // because DLL and DLM have the same address of RHR / THR / IER
    // UART depends on LCR's 7th bit to dicide whether to set divisor latch
    // divisor = ceil((clock_hz) / (baud_sps * 16))
    // we set baud to 38.4K, so divisor = 1.8432M / (38.4K * 16) = 3
    w_reg(LCR, LCR_DIVISOR_LATCH);      // enable divisor latch
    w_reg(DLL, 0x03);
    w_reg(DLM, 0x00);

    // disable divisor latch and set word length to 8
    w_reg(LCR, LCR_WORD_LENGTH);

    // enable receive / transmit interrupt
    w_reg(IER, IER_RT_ENABLE);

    // reset and enable FIFO
    w_reg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_RESET);
}

int putchar(int c) {
    w_reg(THR, c);
    return c;
}

int getchar() {
    if (r_reg(LSR) & 0x01) {
        return r_reg(RHR);
    } else {
        return -1;
    }
}
