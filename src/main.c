#include <stdio.h>
#include "include/sort.h"

int main(void) {
    double A[5] = {
        [0] = 9.0,
        [1] = 2.9,
        [4] = 3.E+25,
        [3] = .00007,
    };

    for (size_t i = 0; i < 5; ++i) {
        if (0){
            printf("element %zu is %g", i, A[i]);
        };
    };
    int B[5];
    sort(B);
}