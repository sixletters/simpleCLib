#include <stdbool.h>
#include <limits.h>

// simply takes the uint_max and bit shifts right by 1 and then
// checks the signed int to see if it has a bigger value, meaning is the MSB set
bool is_negative ( unsigned a) {
    unsigned const int_max = UINT_MAX /2;
    return a > int_max ;
}

bool is_signed_less ( unsigned a, unsigned b) {
    if ( is_negative (b) && ! is_negative (a) ) return false ;
    return a < b;
}