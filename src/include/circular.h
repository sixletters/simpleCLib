#include <stdlib.h>


/**
 * Circular buffer
 * a fixed capacity queue object that wraps around
 * todo: make it thread safe and concurrent in the future
 * todo: support generics and any type
*/
typedef struct circular circular;
struct circular {
    size_t start; /*position of element 0*/
    size_t len; /*num of elements stored*/
    size_t capacity; /*max num elements that can be stored*/
    double* buffer; /*buffer that holds the underlying data*/
};

/**
 * Circular buffer operations
*/
circular* circular_append(circular* c, double x);
double circular_pop(circular* c);
double* circular_element(circular* c, size_t pos);
circular* circular_resize(circular* c, size_t capacity);
size_t circular_getlength(circular* c);

/**
 * Circular Buffer intializers, constructors and destructors
 * To be applied to existing objects, receives a pointer to such an object and ensure there is enough
 * buffer space that is allocated or freed.
*/
circular* circular_init(circular* c, size_t capacity);
void circular_destroy(circular* c);

/**
 * Circular Buffer intializers, constructors and destructors
 * circular_new creates an object and intializes it
*/
circular* circular_new(size_t capacity);
void circular_delete(circular* c);