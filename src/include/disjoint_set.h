#include <stdio.h>


/** Disjoint Set Data structue
    It is defined as a data structure that keep track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
    we shall use a vertice struct to keep track of all vertice information
    and a edge struct to keep track of connections between two vertices
    The union find algorithm does as follows:
    1. Find(X) -> where x is the element in question, finds the representive of the set of which x is a member of. This determines if two elmenets
       are in the same subset
    2. Union(X,Y) - > Join two subsets into a single set
    3. Union_BY_RANK(X, Y) -> join two sets, the set with the larger height takes precedence
    4. Union_BY_SIZE(X, Y) -> join two sets, the set with the bigger size takes precedence
**/
typedef struct vertice vertice;
struct vertice {
    size_t id; /*id of vertice/ element*/
    char* data; /*actual data pointed to by the element*/
};

// structure that represents the connection between two different vertices or elements
typedef struct edge edge;
struct edge {
    size_t ele_1;
    size_t ele_2;
};

// if we want the parent list to be dynamic, we have to allocate it on the heap. rather than on the stack
// lets first assume that our disjoint_set has a fixed number of elements
typedef struct disjoint_set disjoint_set;
struct disjoint_set {
    const size_t num_of_ele;
    size_t parents[]; /* arr[i] is the parent of i, where if arr[i] == [i] then i is the representative of the set*/

};

#define SET_NOT_FOUND -1
// intializes the set with each element being in its own set
void intialize_set(int arr[], size_t n);
// finds the representative of a set, returns -1 if it does not exist
ssize_t find_recursive(int arr[], size_t n, size_t x);
// Given two elements that are part of either 2 different sets or the same set, it unions the sets
ssize_t union_recursive(int[], size_t, size_t, size_t);

// same as above but iteratively
ssize_t find_iterative(int arr[], size_t n, size_t x);
ssize_t union_iterative(int[], size_t, size_t, size_t);