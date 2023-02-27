#include <types.h>
#include <string.h>
#include <kernel.h>
#include <regs.h>
#include <memlayout.h>
#include <mm.h>

extern char _etext[];
pgtb_t kernel_pgtb;

void kvmmap(pgtb_t pgtb, uint64 va, uint64 sz, uint64 pa, int perm) {
    if (mappg(pgtb, va, sz, pa, perm) != 0) {
        panic("kvmmap");
    }
}

int mappg(pgtb_t pgtb, uint64 va, uint64 sz, uint64 pa, int perm) {
    uint64 a, lst;
    pte_t *pte;

    if (sz == 0) {
        panic("mappg: sz == 0");
    }
    a = PGDOWN(va);
    lst = PGDOWN(va + sz - 1);
    while (1) {
        if ((pte = walk(pgtb, a, 1)) == 0) {
            return -1;
        }
        if (*pte & PTE_V) {
            panic("mappg: remap");
        }
        *pte = PA2PTE(pa) | perm | PTE_V;
        if (a == lst) {
            break;
        }
        a += PGSIZE;
        pa += PGSIZE;
    }
    return 0;
}

pte_t *walk(pgtb_t pgtb, uint64 va, int alloc) {
    int level;
    pte_t *pte;

    if (va >= MAXVA) {
        panic("walk");
    }
    for (level = 2; level > 0; level--) {
        pte = &pgtb[PX(level, va)];
        if (*pte & PTE_V) {
            pgtb = (pgtb_t) PTE2PA(*pte);
        } else {
            if (!alloc || (pgtb = (pgtb_t) kalloc()) == 0) {
                return 0;
            }
            memset(pgtb, 0, PGSIZE);
            *pte = PA2PTE(pgtb) | PTE_V;
        }
    }
    return &pgtb[PX(0, va)];
}

pgtb_t kvmmake() {
    pgtb_t pgtb;

    pgtb = (pgtb_t) kalloc();
    memset(pgtb, 0, PGSIZE);
    kvmmap(pgtb, UART0, PGSIZE, UART0, PTE_R | PTE_W);
    kvmmap(pgtb, KERNELBASE, (uint64) _etext - KERNELBASE, KERNELBASE,
            PTE_R | PTE_X);
    kvmmap(pgtb, (uint64) _etext, PHYSTOP - (uint64) _etext, (uint64) _etext,
            PTE_R | PTE_W);
    return pgtb;
}

void kvminit() {
    kernel_pgtb = kvmmake();
    w_satp(MAKE_SATP(kernel_pgtb));
    sfence_vma();
}
