#include <stddef.h>
#include <stdio.h>

unsigned long Strtoul_inner(char const s[1], size_t i, unsigned base);
unsigned long Strtoul(char const s[1], unsigned base);