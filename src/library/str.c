#include "../include/log.h"
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>


unsigned hexatridecimal(int a) {
    if (isdigit(a)) {
        return a - '0';
    }
    a = toupper(a);
    return (isupper(a)) ? 10 + (a - 'A'): -1;
}

unsigned long Strtoul_inner(char const s[static 1], size_t i, unsigned base){
    unsigned long ret = 0;
    while (s[i]) {
        unsigned c = hexatridecimal(s[i]);
        if (c >= base) break;
        if (ULONG_MAX/base < ret) {
            ret = ULONG_MAX;
            errno = ERANGE;
            break;
        }
        ret *= base;
        ret += c;
        ++i;
    }
    return ret;
}

unsigned long Strtoul(char const s[static 1], unsigned base){
    if(base > 36u) {
        errno = EINVAL;
        return ULONG_MAX;
    }
    size_t i = strspn(s, "␣\f\n\r\t\v");
    bool switchsign = false;
    switch (s[i])
    {
    case '-': 
        switchsign = true;
        break;
    case '+':
        ++i;
    }
    if (!base || base == 16) {
        size_t adj = find_prefix(s, i, "0x");
        if (!base) base = (unsigned[]){10, 8, 16, }[adj];
        i += adj;
    }
    unsigned long ret = Strtoul_inner(s, i, base);
    return switchsign ? - ret: ret;
}