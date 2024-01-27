#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "./../include/sort.h"
#include "./../include/log.h"
#include <unistd.h>

#define NUM_SORT_TESTCASES 5
#define TESTCASE_ARR_SIZE 6

int test_sort(int sort_type);

// Allocated during compile time, they are and should be packed together
// interesting thing disocvered, but C pads values that are not given with 0
const int test_case_arr[NUM_SORT_TESTCASES][TESTCASE_ARR_SIZE] =  {{1,2,3,4,5}, {4,8,3,-1,4,1}, {1}, {6,5,4,3,2}, {4}};
const size_t arr_sizes[NUM_SORT_TESTCASES] = {5,6,1,5,1};
// Read only
const int expected_arr[NUM_SORT_TESTCASES][TESTCASE_ARR_SIZE] = {{1,2,3,4,5}, {-1,1,3,4,4,8}, {1}, {2,3,4,5,6}, {4}};

void deep_copy_2d_arr(void* src, void* dest, size_t rows, size_t cols, size_t mem_size) {
    memcpy(dest, src, rows * cols * mem_size);
}

int test_sort(int sort_type) {
    int testcases[NUM_SORT_TESTCASES][TESTCASE_ARR_SIZE];
    int (*comparator)(void *, void *) = (int (*)(void *, void *))&int_compare;
    deep_copy_2d_arr((void*)test_case_arr, (void*)testcases, NUM_SORT_TESTCASES, TESTCASE_ARR_SIZE, sizeof(int));

    for(int i = 0; i < NUM_SORT_TESTCASES; i++){
        switch (sort_type)
        {   
            // Take note that merge and quick sort takes the right index, whereas bubble and insertion sort takes the size
            case 0:
                merge_sort((void*)(testcases[i]), sizeof(int), 0, arr_sizes[i]-1, comparator);
                break;
            case 1:
                quick_sort((void*)(testcases[i]), sizeof(int), 0, arr_sizes[i]-1, comparator);
                break;
            case 2:
                insertion_sort((void*)(testcases[i]), sizeof(int), arr_sizes[i], comparator);
                break;
            case 3:
                bubble_sort((void*)(testcases[i]), sizeof(int), arr_sizes[i], comparator);
                break;
            default:
                error("unrecognized sort type");
                break;
        }
    }
    for(int i = 0; i < NUM_SORT_TESTCASES; i++){
        for(int j = 0; j < arr_sizes[i];j++){
            // only uncomment when debugging
            // debug("%d, %d",testcases[i][j], expected_arr[i][j]);
            assert(testcases[i][j] == expected_arr[i][j]);
        }
    }
    switch (sort_type)
    {   
        case 0:
            info("mergesort testcases passed");
            break;
        case 1:
            info("quicksort testcases passed");
            break;
        case 2:
            info("insertionsort testcases passed");
            break;
        case 3:
            info("bubblesort testcases passed");
            break;
        default:
            break;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]){
    if(argc != 2 ){
        fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
        fprintf(stderr, "Where NUMBER is right of the following:\n");
        fprintf(stderr, "    0. Test merge_sort\n");
        fprintf(stderr, "    1. Test quick_sort\n");
        fprintf(stderr, "    2. Test insertion_sort\n");
        fprintf(stderr, "    3. Test bubble_sort\n");
        return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    if(number <0 || number > 3){
        fprintf(stderr, "Unknown NUMBER: %d\n", number);
        return EXIT_FAILURE;
    }

    return test_sort(number);
}