
#include <stddef.h>
#include "../include/log.h"

void sort(int* arr){
    return;
};

void merge(void *v, size_t l , size_t m, size_t r, size_t mem_size, int (*comp)(void*, void*));

/**
    Generic implementation of merge sort in c, takes in a comparator function
    The merge sort implementation is as follows
    4,8,3,6,1,2
    1. Create and populate two arrays from left to mid and mid+1 to right
    2. if right > left: continue, else return
    2. merge sort from left to mid and mid+1 to right
    3. Merge
        Iterate through using 2 pointers, and overwrite value of original arr
**/
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
    // Copy left over values into original array
    while(i < n1) {
        memcpy((char*)v + (k++ * mem_size), L + (i++ * mem_size), mem_size);
    }

    while(j < n2) {
        memcpy((char*)v + (k++ * mem_size), R + (j++ * mem_size), mem_size);
    }
}

int int_compare(void* ele1, void* ele2) {
    // casting s1 to int* so it can be 
    // copied in variable a. 
    int *a = (int*)ele1; 
    int *b = (int*)ele2; 
    return *a < *b;
}

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

/**
    Generic implementation of quick sort in C, takes in a comparator function
    The quick sort implementation is as follows
    4,8,3,6,1,2
    1. Choose partition ( this implementation uses the mid index as partition ), 3 is the partition.
    2. Swap arr[partition] and arr[right]. swap 3 and 2 -> 4,8,2,6,1,3.
    3. Init a swap ptr = left.
    4. Iterate from i = 0 till i = right -1,
        (This works because, for cases where i == swap_ptr, it will get swapped with itself
        For cases where arr[i] > mid: 
            while i increases, the swap_ptr will get left behind at the index that is bigger than partition)
        if arr[i] < mid:
            swap arr[i] and arr[swap_ptr]
            swap_ptr++
    5. Swap back the arr[right] and arr[swap_ptr].
    6. quick sort on range from left to swap_ptr-1 and swap_ptr+1 to right.
**/
void quick_sort(void *v, size_t mem_size, size_t left, size_t right, int (*comp)(void*, void*)){
    // if right is smaller than or equals to left, then return
    if(right <= left) return;
    // find pivot
    size_t pivot = ((left+right)/2);
    // swap pivot with the value in arr[right]
    char* vp = (char*)(v + pivot * mem_size);
    char* vr = (char*)(v + right * mem_size);
    swap(vp, vr, mem_size);
    size_t swap_ptr = left;
    char* curr;

    // iterate from left to right-1
    size_t i = left;
    while (i < right){
        curr = (char*)(v + (i * mem_size));
        // if it should be smaller then swap arr[i] and arr[swap_ptr]
        if(comp(curr, vr)){
            char* to_swap = (char*)(v + (swap_ptr * mem_size)); 
            swap(curr, to_swap, mem_size);
            swap_ptr++;
        } 
        // swap_ptr gets left behind at values that should be after mid
        i++;
    } 
    // swap partition value to rightful place
    char* to_swap = (char*)(v + (swap_ptr * mem_size)); 
    swap(vr, to_swap, mem_size);
    // quick sort from left to swap_ptr-1 and swap_ptr+1 to right
    // swap_ptr is the new position of the partition value
    if(swap_ptr != 0) {
        quick_sort(v, mem_size, left, swap_ptr-1, comp);
    }
    quick_sort(v, mem_size, swap_ptr+1, right, comp);
}

/**
    Generic implementation of insertion sort in C. Insertion sort algortihm can be thought of like this
    imagine an element K of index i an arr, we can assume that arr[0.... i-1] is already is in sorted order,
    we simply have to find the correct place to insert this element K, it can be done by saving a copy of K and then moving all elements
    that should be after it one position forward, when we reach an element that is smaller or equal than it, we know that K should be one after it.
    1. Iterate from 1 to n as i
    2. store curr = arr[i]
    3. j = i - 1
    4. while j >= 0 and arr[j] > curr
        4.1 swap arr[j] and arr[j+1] (this will be curr, for the first iteration)
        4.2 j -=1
**/
void insertion_sort(void *v, size_t mem_size, size_t n,  int (*comp)(void*, void*)){
    for(size_t i = 1; i < n; i ++){
        char curr[mem_size];
        memcpy(curr, (v + (i*mem_size)), mem_size);
        int j = i - 1;
        while(j >= 0 && comp(curr, (v + (j*mem_size)))){
            swap(v+((j+1)*mem_size), v+(j*mem_size), mem_size);
            j -= 1;
        }
    }
}

/**
 *  Generic Implementation of the bubble sort
 *  Easiest sort to implement probably
 *  Keep bubbling the biggest number to the end and then decerment the end by 1 since the biggest number is already there,
 *  then bubble the next biggest number to end (after its been decremented by 1)
 * 
**/
void bubble_sort(void *v, size_t mem_size, size_t n,  int (*comp)(void*, void*)){
    for(ssize_t i = n - 1 ; i >= 0; i--){
        for(ssize_t j = 0; j < i; j++){
            if(!comp(v + (j * mem_size), v + ((j+1) * mem_size))){
                swap(v+((j+1)*mem_size), v+(j*mem_size), mem_size);
            }
        }
    }
}