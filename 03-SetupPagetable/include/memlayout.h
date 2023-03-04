#ifndef _MEMLAYOUT_H
#define _MEMLAYOUT_H

#define UART0           0x10000000L
#define KERNELBASE      0x80000000
#define MEMSIZE         (128 * 1024 * 1024)
#define PHYSTOP         (KERNELBASE + MEMSIZE)
                            
#endif
