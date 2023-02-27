#include <types.h>
#include <string.h>
#include <uart.h>
#include <printf.h>
#include <mm.h>

extern pgtb_t kernel_pgtb;

void print_pgtb(pgtb_t pg, int level);

void main() {
    int c;

    uartinit();
    printf("Hello world!\n");

    mem_init();
    kvminit();

    printf("page table %p\n", kernel_pgtb);
    print_pgtb(kernel_pgtb, 0);

    while (1) {
        c = getchar();
        if (c != -1) {
            switch (c) {
                case 8: case 127:
                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                    break;
                case 10: case 13:
                    putchar('\n');
                    break;
                default:
                    putchar(c);
            }
        }
    }
}

void print_pgtb(pgtb_t pg, int level) {
    int i, j;
    pte_t pte;

    for (i = 0; i < 8; i++) {
        pte = pg[i];
        if (pte & PTE_V) {
            for (j = 0; j <= level; j++) {
                printf("-- ");
            }
            uint64 child = PTE2PA(pte);
            printf("%d: pte %p, pa %p\n", i, pte, child);
            if (level == 2) {
                continue;
            } else {
                print_pgtb((pgtb_t) child, level + 1);
            }
        }
    }
}
