/**
 * Circular buffer implementations
*/

#include "../include/log.h"
#include "../include/circular.h"

// intializes a circular buffer object
circular* circular_init(circular* c, size_t capacity) {
    // check C for validaity, null pointers should be set to 0
    if (c) {
        // make sure capacity is not 0
        // malloc indicated failure by returning a null pointer value
        if(capacity) {
            *c = (circular){
                .capacity = capacity,
                .buffer = malloc(sizeof(double[capacity])),
            };
            // failed heap allocation
            // reasons could be 
            // 1. memory exhaustion
            // 2. too large size
            if(!c->buffer) c->capacity = 0;
        }else {
            *c = (circular){0};
        }
    }
    return c;
}

// constructor for a circular buffer object, initializes on the heap
circular* circular_new(size_t capacity){
    circular* c = malloc(sizeof(circular));
    if(c) {
        circular_init(c, capacity);
    }
    return c;
}

// destructor for the circular buffer object, allocated on the heap
void circular_delete(circular* c){
    if(c) {
        circular_destroy(c);
        free(c);
    }
}

// dis-initializer for the circular buffer object
void circular_destroy(circular *c) {
    if (c) {
        // if null pointer receive, free does nothing
        free(c->buffer);
        circular_init(c, 0);
    }
}

// Static funations are one whose scope is limited to the file in which it is declated
// meaning you cannoext acces this function from any other files
// it helps to encapsulate and hide implementation, and also does not invade the identifier namespace
static size_t circular_getpos(circular* c, size_t pos) {
    pos += c->start;
    pos %= c->capacity;
    return pos;
}

double* circular_element(circular* c, size_t pos){
    double* ret = 0;
    if( c ) {
        // fetch actual index in the buffer
        pos = circular_getpos(c, pos);
        ret = &(c->buffer[pos]);
    }
    return ret;
}

circular* circular_resize(circular* c, size_t n_cap){
    if (c) {
        size_t len = c->len;
        // if curr num of elements is more than new capacity, return 0 (error)
        if (len > n_cap) return 0;
        size_t o_cap = c->capacity;
        if (n_cap != o_cap){
            size_t o_start = c->start;
            size_t n_start = c->start;
            double* o_buffer = c->buffer;
            double* n_buffer = c->buffer;
            // two seperate cases have to be handled seperately,
            // the timing at which the reallac is called is crucial
            if (n_cap > o_cap){
                // case for when there is a capacity increase
                n_buffer = realloc(o_buffer, sizeof(double[n_cap]));
                if (!n_buffer) return 0;
                // wraps around, if it doesnt wrap around we, dont need to handle
                if(o_start + len > o_cap) {
                    // num in first of 
                    size_t ulen = o_cap - o_start;
                    // num in second half
                    size_t ilen = len - ulen;
                    // basically if there is room for the second half in the added capacity, move the wrap around down
                    // if not then move the first half to the end and set start
                    if (ilen <= (n_cap - o_cap)) {
                        memcpy(n_buffer+o_cap, n_buffer, ilen * sizeof ( double ));
                    } else{
                        n_start = (n_cap -  ulen);
                        memcpy(n_buffer+n_start, n_buffer + o_start, ulen * sizeof ( double ));
                    }
                }
            }else{
                 // for when there is a capacity decrease
                // wraps around, if it doesnt wrap around we, dont need to handle
                if(o_start + len > o_cap) {
                    // num in first 
                    size_t ulen = o_cap - o_start;
                    // we have to shift the first half back by delta
                    n_start = o_start - (o_cap - n_cap);
                    memcpy(o_buffer + n_start, o_buffer + o_start, sizeof(double) * ulen);
                }
                // case for when there is a capacity increase
                n_buffer = realloc(o_buffer, sizeof(double[n_cap]));
            }
            *c = (circular) {
                .capacity = n_cap,
                .start = n_start,
                .len = len,
                .buffer = n_buffer,
            };
        }
     }
    return c;
}

circular* circular_append(circular* c, double x) {
    if (c) {
        // end(index to insert) = start + len
        // % capacity needed as it wraps around
        c->buffer[((c->start) + c->len) % c->capacity] = x;
        if(c->len < c->capacity) {
            c->len++;
        }
    }
    return c;
}

double circular_pop(circular* c) {
    double ret = 0;
    // can only pop if there is at least one element in C
    if(c && circular_getlength(c) > 0) {
        ret = c->buffer[c->start];
        c->len--;
        c->start++;
        c->start = c->start % c->capacity;
    }
    return ret;
}

size_t circular_getlength(circular* c){
    if(c) {
        return c->len;
    }
    return 0;
}

double max(double a, double b){
    if(a > b){
        return a;
    }
    return b;
}

double min(double a, double b){
    if(a < b){
        return a;
    }
    return b;
}

