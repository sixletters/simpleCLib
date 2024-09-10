#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "./../include/sort.h"
#include "./../include/log.h"
#include "./../include/disjoint_set.h"
#include <unistd.h>


int test_find_iterative();
int test_union_iterative();
int test_path_compression_iterative();

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0. Test find\n");
        fprintf(stderr, "    1. Test union\n");
        fprintf(stderr, "    2. Test path compression\n");
        return EXIT_FAILURE;
    }
    int number = atoi(argv[1]);
        if(number <0 || number > 3){
        fprintf(stderr, "Unknown NUMBER: %d\n", number);
        return EXIT_FAILURE;
    }
    
    int status = 0;
    switch(number) {
        case 0: status = test_find_iterative(); break;
        case 1: status = test_union_iterative(); break;
        case 2: status = test_path_compression_iterative(); break;
        default: fprintf(stderr, "Unknown NUMBER: %d\n", number); break;
    }
    return status;
}

int test_find_iterative() {
    int test[5];
    // 0 1 2 3 4
    intialize_set(test, 5);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 1);

    assert(test[0] == 1);
    assert(test[1] == 1);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 2);

    assert(test[0] == 2);
    assert(test[1] == 2);
    assert(test[2] == 2);
    return EXIT_SUCCESS;
}

int test_union_iterative() {
    int test[5];
    // 0 1 2 3 4
    intialize_set(test, 5);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 1);

    assert(test[0] == 1);
    assert(test[1] == 1);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 2);

    assert(test[0] == 2);
    assert(test[1] == 2);
    assert(test[2] == 2);
    return EXIT_SUCCESS;
}

int test_path_compression_iterative(){
    int test[5];
    // 0 1 2 3 4
    intialize_set(test, 5);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 1);

    assert(test[0] == 1);
    assert(test[1] == 1);

    // 1 1 2 3 4
    union_iterative(test, 5, 0, 2);

    assert(test[0] == 2);
    assert(test[1] == 2);
    assert(test[2] == 2);
    return EXIT_SUCCESS;
}