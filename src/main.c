#include <stdio.h>
#include "include/sort.h"
#include "include/log.h"

int main(void) {
    // double A[5] = {
    //     [0] = 9.0,
    //     [1] = 2.9,
    //     [4] = 3.E+25,
    //     [3] = .00007,
    // };

    // for (size_t i = 0; i < 5; ++i) {
    //     if (0){
    //         // printf("element %zu is %g", i, A[i]);
    //     };
    // };

    int (*comparator)(void *, void *) = (int (*)(void *, void *))&int_compare;
    int arr[5] = {4,2,5,6,7};
    
    // bubble_sort(arr, sizeof(int),6, comparator);
    quick_sort(arr, sizeof(int),0, 4, comparator);
    for (size_t i = 0; i <= 4; ++i) {
        info("element is %d", arr[i]);
    };
}