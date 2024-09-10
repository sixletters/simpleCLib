#include <stddef.h>
#include "../include/log.h"
#include <stdio.h>


void intialize_set(int arr[], size_t n) {
    for(size_t i=0; i < n; i++){
        arr[i] = i;
    }
}

void swap(void* x, void* y) {
    void * temp = x;
    x = y;
    y = temp;
}

void intialize_set_with_size(int arr[], int size[], size_t n) {
    for(size_t i=0; i < n; i++){
        arr[i] = i;
        size[i] = 1;
    }
}

ssize_t find_recursive(int parents[], int weights[], size_t n, size_t x) {
    if(x > n){
        return -1;
    }
    if (x == parents[x]) {
        return  x;
    }
    // tail recursion is better
    int currParent = parents[x];
    int newParent = find_recursive(parents, weights, n, x);
    weights[currParent] -= 1;
    weights[newParent] += 1;
    return newParent;
}


/*
* Union find iterative algorithm with path compression
* Given a parents array, or set we look for the representative of x
* This is done by iterative traversing thru the parent array until an element is its own parent
*/
ssize_t find_iterative(int parents[], size_t n, size_t x) {
    if(x > n){
        return -1;
    }
    int child = x;
    int parent = parents[x];
    // todo : see if there is better semantics for this
    int childList[n];
    int num_of_children = 1;
    // keep going while it is not its own parent
    while(parent != parents[parent]) {
        // collect number of children and all children of current parent
        childList[num_of_children] = child;
        num_of_children++;

        // parent of child becomes the new child
        child = parent;
        // parent of parent becomes the new parnte
        parent = parents[parent];
    }
    // perform path compression, set all parent of child to new parent
    for(int i = 0; i <num_of_children;i++){
        parents[childList[i]] = parent;
    }
    return parent;
}

ssize_t union_recursive(int parents[], int weights[], size_t n, size_t x, size_t y) {
    int x_root = find_recursive(parents, weights, n, x);
    int y_root = find_recursive(parents, weights, n, y);
    if(x_root != y_root) {
        if (weights[x_root] < weights[y_root]) {
            // if the weight of y is bigger then swap
            swap(x_root, y_root);
        }
        // x will be y's new child
        parents[y_root] = x_root;
        // add new weight to x
        weights[x_root] += weights[y_root];
        return x_root;
    }
    return x_root;
    // By rank and by size can be done here
}


ssize_t union_iterative(int parents[], size_t n, size_t x, size_t y) {
    int x_root = find_iterative(parents, n, x);
    int y_root = find_iterative(parents, n, y);

    // todo: By rank and by size can be done here
    parents[x_root] = y_root;
}


