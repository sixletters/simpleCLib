
#include <stddef.h>
#include "../include/log.h"

void sort(int* arr){
    return;
};

void merge(void *v, size_t l , size_t m, size_t r, size_t mem_size, int (*comp)(void*, void*));
// Generic implementation of merge sort in C, takes in a comparator function
// comparator should return true if first element should be before second element
void merge_sort(void *v, size_t mem_size, size_t left, size_t right, int (*comp)(void*, void*)){
    size_t mid = (left + right ) / 2;
    // info("mid is %zu", mid);
    if ( right > left) {
        // left side sort from 0 to mid
        merge_sort(v, mem_size, left, mid, comp);
        // right side sort from mid + 1 to size
        merge_sort(v, mem_size, mid+1, right, comp);
        // merge 
        merge(v, left, mid, right, mem_size, comp);
    }
}

int int_compare(int* ele1, int* ele2) {
    return *ele1 < *ele2;
}

int str_compare(char* ele1, char* ele2) {
    return *ele1 < *ele2;
}

// comparator should return true if first element should be before second element
void merge(void *v, size_t l , size_t m, size_t r, size_t mem_size, int (*comp)(void*, void*)) {
    size_t n1 = m - l + 1;
    size_t n2 = r - m;
    // Use a char (bytes) to intialize temp array, mem_size is size of object in memory
    char L[n1 * mem_size], R[n2 * mem_size];
    for (size_t i = 0; i < n1; i++){
        memcpy(L + (i * mem_size), (char *)v + ((l + i) * mem_size), mem_size);
    }
    for (size_t i = 0; i < n2; i++){
        memcpy(R + (i * mem_size), (char *)v + ((m + 1 + i) * mem_size), mem_size);
    }  

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if(comp(L + (i * mem_size), R + (j * mem_size))) {
            memcpy((char*)v + (k++ * mem_size), L + (i++ * mem_size), mem_size);
        } else{
            memcpy((char*)v + (k++ * mem_size), R + (j++ * mem_size), mem_size);
        }
    }
    while(i < n1) {
        memcpy((char*)v + (k++ * mem_size), L + (i++ * mem_size), mem_size);
    }

    while(j < n2) {
        memcpy((char*)v + (k++ * mem_size), R + (j++ * mem_size), mem_size);
    }
}

void swap(void* v1, void* v2, int size){

    // Buffer is an array of characters that stores elements
    // byte by byte
    char buffer[size];

    // Copy to respective memory locations
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

// Generic implementation of quick sort in C, takes in a comparator function
void quick_sort(void *v, size_t size, size_t left, size_t right, int (*comp)(void*, void*)){

}