#include <types.h>
#include <regs.h>

extern void main();

/*
 * boot.S jump to here in machine mode
 * set CSRs (Control and Status Registers) to transfer to supervisor mode
 * then return to main function.
 *
 * read chapter 3 of the following pdf to get some info about M-level ISA.
 * https://riscv.org/wp-content/uploads/2017/05/riscv-privileged-v1.10.pdf
 */
void start() {
    // close M-mode enter S-mode after mret
    w_mstatus((r_mstatus() & ~MSTATUS_MPP_M) | MSTATUS_MPP_S);

    // get function main's address for mret
    // mret will copy mepc to pc
    w_mepc((uint64) main);

    // disable paging for now
    w_satp(0);

    // configure Physical Memory Protection to give supervisor mode
    // access to all of physical memory.
    w_pmpcfg0(0xf);
    w_pmpaddr0(0x3fffffffffffffull);

    asm volatile("mret");
}
