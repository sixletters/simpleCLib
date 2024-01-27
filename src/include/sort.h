
void sort(int* arr);

int int_compare(int* ele1, int* ele2);
void merge_sort(void *v, size_t mem_size, size_t left, size_t right, int (*comp)(void*, void*));
void quick_sort(void *v, size_t mem_size, size_t left, size_t right, int (*comp)(void*, void*));
void insertion_sort(void *v,size_t memsize, size_t n, int (*comp)(void*, void*));
void bubble_sort(void *v, size_t memsize, size_t n, int (*comp)(void*, void*));