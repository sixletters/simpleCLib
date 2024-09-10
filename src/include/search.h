#include <stddef.h>
#include <sys/types.h>
#include "../include/log.h"


#define SEARCH_INDEX_FAILURE    (-1)

ssize_t binary_search(void *arr, size_t n, size_t mem_size, void* val, int (*comp)(void*, void*));
char* quick_select(void *arr, size_t mem_size, size_t left, size_t right, int k, int (*comp)(void*, void*));

// int int_compare(void* ele1, void* ele2) {
//     // casting s1 to int* so it can be 
//     // copied in variable a. 
//     int *a = (int*)ele1; 
//     int *b = (int*)ele2; 
//     return *a < *b;
// }

int str_compare(void* ele1, void* ele2) {
    char *a1 = *(char**)ele1;
    char *a2 = *(char**)ele2; 
    return strcmp(a1, a2);  
}

void swap(void* v1, void* v2, size_t size){
    // Buffer is an array of characters that stores elements
    // byte by byte
    char buffer[size];

    // Copy to respective memory locations
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

ssize_t binary_search(void *arr, size_t n, size_t mem_size, void* val, int (*comp)(void*, void*)) {
    if(n == 0){
        return SEARCH_INDEX_FAILURE;
    }
    int l = 0;
    int r = n-1;
    while(l < r) {
        int mid = (l + r)/2 + 1;
        void * mid_value = arr + (mem_size * mid);
        if (comp(mid_value, val) == 1 || comp(mid_value, val)== 0 ) {
            debug("%d", l);
            debug("%d", r);
            l = mid;
        } else{
            debug("%d", l);
            r = mid - 1;
        }
    }
    return l;
}

char* quick_select(void *arr, size_t mem_size, size_t left, size_t right, int k, int (*comp)(void*, void*)) {
    if(right <= left) return NULL;
    // first find the pivot
    size_t pivot = ((left+right)/2);

    char* vp = (char*)(arr + pivot * mem_size);
    char* vr = (char*)(arr + right * mem_size);
    swap(vp, vr, mem_size);
    size_t swap_ptr = left;
    char* curr;
    // swap the pivot with the value in arr[right]
    size_t i = left;
    while(i < right) {
        curr = (char*)(arr + i * mem_size);
        if(comp(curr, vr)){
            char* to_swap = (char*)(arr + (swap_ptr * mem_size)); 
            swap(curr, to_swap, mem_size);
            swap_ptr++;
        }
        i++;
    }
    // swap partition value to rightful place
    char* to_swap = (char*)(arr + (swap_ptr * mem_size));

    swap(vr, to_swap, mem_size);
    // if the partition itself is the kth biggest, than return partition 
    if(swap_ptr == k){
        return to_swap;
    } else if (k > swap_ptr) {
         return quick_select(arr, mem_size, swap_ptr+1, right, k - swap_ptr - 1, comp);
    }
    return quick_select(arr, mem_size, left, swap_ptr-1, k, comp);
}

