#include <types.h>
#include <string.h>
#include <uart.h>
#include <mm.h>

extern char _etext[];

void main() {
    int c;
    pgtb_t pgtb;
    pte_t *pte;

    uartinit();
    print("Hello world!\n");

    mem_init();
    pgtb = (pgtb_t) kalloc();
    memset(pgtb, 0, PGSIZE);
    kvmmap(pgtb, (uint64) _etext, PHYSTOP - (uint64) _etext, (uint64) _etext,
            PTE_R | PTE_W);
    pte = walk(pgtb, (uint64) _etext, 0);
    // printf("%lld => %lld\n", (uint64) _etext, PTE2PA(*pte));
    printint((uint64) _etext);
    print(" => ");
    printint((uint64) PTE2PA(*pte));
    print("\n");

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
