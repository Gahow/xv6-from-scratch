#ifndef _STRING_H
#define _STRING_H

#include <types.h>

void *memset(void *s, int c, int n);
char *to_string(uint64 n);
void reverse(char *str);

#endif
