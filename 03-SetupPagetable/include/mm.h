#ifndef _MM_H
#define _MM_H

#define MAXVA           (1L << (9 + 9 + 9 + 12 - 1))
#define PGSHIFT         12
#define PGSIZE          (1 << PGSHIFT)
#define PGMASK          (PGSIZE - 1)
#define PTE_V           (1 << 0)
#define PTE_R           (1 << 1)
#define PTE_W           (1 << 2)
#define PTE_X           (1 << 3)
#define PTE_U           (1 << 4)
#define PXMASK          0x1FF

#define PGUP(pa)        (((pa) + PGSIZE - 1) & ~PGMASK)
#define PGDOWN(pa)      ((pa) & ~PGMASK)
#define PA2PTE(pa)      ((((uint64) pa) >> 12) << 10)
#define PTE2PA(pte)     ((((uint64) pte) >> 10) << 12)
#define PXSHIFT(level)  (PGSHIFT + 9 * (level))
#define PX(level, va)   (((uint64) va >> PXSHIFT(level)) & PXMASK)

void mem_init();
void free_range(char *pa_start, char *pa_end);
void free_page(char *pa);
void *kalloc();

void    kvmmap(pgtb_t pgtb, uint64 va, uint64 sz, uint64 pa, int perm);
int     mappg(pgtb_t pgtb, uint64 va, uint64 sz, uint64 pa, int perm);
pte_t   *walk(pgtb_t pgtb, uint64 va, int alloc);
pgtb_t  kvmmake();
void    kvminit();

#endif
