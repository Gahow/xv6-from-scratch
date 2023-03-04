#include <types.h>
#include <kernel.h>
#include <string.h>
#include <memlayout.h>
#include <mm.h>

extern char _end[];

struct page {
    struct page *nxt;
};

struct {
    struct page *free_list;
} kmem;

void mem_init() {
    free_range((char *) _end, (char *) PHYSTOP);
}

void free_range(char *pa_start, char *pa_end) {
    char *p;

    p = (char *) PGUP((uint64) pa_start);
    for ( ; p < (char *) pa_end; p += PGSIZE) {
        free_page(p);
    }
}

void free_page(char *pa) {
    struct page *pg;

    if ((uint64) pa % PGSIZE != 0 || pa < _end || (uint64) pa > PHYSTOP) {
        panic("free_page");
    }
    memset(pa, 0, PGSIZE);
    pg = (struct page *) pa;
    pg->nxt = kmem.free_list;
    kmem.free_list = pg;
}

void *kalloc() {
    struct page *pg;

    pg = kmem.free_list;
    if (pg) {
        kmem.free_list = pg->nxt;
        memset((void *) pg, 0, PGSIZE);
    }
    return (void *)pg;
}
