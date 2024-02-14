#include <stddef.h>
#include "../include/log.h"
#include <stdio.h>


void intialize_set(int arr[], size_t n) {
    for(size_t i=0; i < n; i++){
        arr[i] = i;
    }
}


ssize_t find(int parents[], size_t n, size_t x) {
    if(x > n){
        return -1;
    }
    int parent = parents[x];
    while(parent != parents[parent]) {
        parent = parents[parent];
    }
    return parent;
}

ssize_t union_(int parents[], size_t n, size_t x, size_t y) {
    int x_root = find(parents, n, x);
    int y_root = find(parents, n, y);

    parents[x_root] = y_root;
}

