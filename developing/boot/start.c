#include <types.h>

// Machine Previous Privilege
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)

// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9)
#define SIE_STIE (1L << 5)
#define SIE_SSIE (1L << 1)

uint64 r_mstatus() {
    uint64 x;
    asm volatile("csrr %0, mstatus" : "=r" (x));
    return x;
}

void w_mstatus(uint64 x) {
    asm volatile("csrw mstatus, %0" : : "r" (x));
}

void w_mepc(uint64 x) {
    asm volatile("csrw mepc, %0" : : "r" (x));
}

void w_satp(uint64 x) {
    asm volatile("csrw satp, %0" : : "r" (x));
}

void w_medeleg(uint64 x) {
    asm volatile("csrw medeleg, %0" : : "r" (x));
}

void w_mideleg(uint64 x) {
    asm volatile("csrw mideleg, %0" : : "r" (x));
}

uint64 r_sie() {
    uint64 x;
    asm volatile("csrr %0, sie" : "=r" (x));
    return x;
}

void w_sie(uint64 x) {
    asm volatile("csrw sie, %0" : : "r" (x));
}

void w_pmpcfg0(uint64 x) {
    asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

void w_pmpaddr0(uint64 x) {
    asm volatile("csrw pmpaddr0, %0" : : "r" (x));
}

extern void main();

/*
 * boot.S jump to here in machine mode
 * set CSRs (Control and Status Registers) to transfer to supervisor mode
 * then return to main function
 */
void start() {
    w_mstatus((r_mstatus() & ~MSTATUS_MPP_M) | MSTATUS_MPP_S);

    w_mepc((uint64) main);

    w_satp(0);

    w_medeleg(0xffff);
    w_mideleg(0xffff);
    w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

    w_pmpcfg0(0xf);
    w_pmpaddr0(0x3fffffffffffffull);

    asm volatile("mret");
}
