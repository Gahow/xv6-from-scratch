#ifndef _REGS_H
#define _REGS_H

// Machine Previous Privilege
#define MSTATUS_MPP_M (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
#define MSTATUS_MPP_U (0L << 11)

// Supervisor Interrupt Enable
#define SIE_SEIE (1L << 9)
#define SIE_STIE (1L << 5)
#define SIE_SSIE (1L << 1)

// use riscv's sv39 page table scheme.
#define SATP_SV39       (8L << 60)
#define MAKE_SATP(pgtb) (SATP_SV39 | (((uint64) pgtb) >> 12))

static inline uint64 r_mstatus() {
    uint64 x;
    asm volatile("csrr %0, mstatus" : "=r" (x));
    return x;
}

static inline void w_mstatus(uint64 x) {
    asm volatile("csrw mstatus, %0" : : "r" (x));
}

static inline void w_mepc(uint64 x) {
    asm volatile("csrw mepc, %0" : : "r" (x));
}

static inline void w_satp(uint64 x) {
    asm volatile("csrw satp, %0" : : "r" (x));
}

static inline void w_medeleg(uint64 x) {
    asm volatile("csrw medeleg, %0" : : "r" (x));
}

static inline void w_mideleg(uint64 x) {
    asm volatile("csrw mideleg, %0" : : "r" (x));
}

static inline uint64 r_sie() {
    uint64 x;
    asm volatile("csrr %0, sie" : "=r" (x));
    return x;
}

static inline void w_sie(uint64 x) {
    asm volatile("csrw sie, %0" : : "r" (x));
}

static inline void w_pmpcfg0(uint64 x) {
    asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

static inline void w_pmpaddr0(uint64 x) {
    asm volatile("csrw pmpaddr0, %0" : : "r" (x));
}

// flush the TLB.
static inline void sfence_vma() {
    asm volatile("sfence.vma zero, zero");
}

/*
static inline uint64  r_mstatus();
static inline void    w_mstatus(uint64 x);
static inline void    w_mepc(uint64 x);
static inline void    w_satp(uint64 x);
static inline void    w_medeleg(uint64 x);
static inline void    w_mideleg(uint64 x);
static inline uint64  r_sie();
static inline void    w_sie(uint64 x);
static inline void    w_pmpcfg0(uint64 x);
static inline void    w_pmpaddr0(uint64 x);

static inline void    sfence_vma();
*/
#endif
