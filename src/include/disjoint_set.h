#include <stdio.h>

/** Disjoint Set Data structue
    It is defined as a data structure that keep track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
    The union find algorithm does as follows:
    1. Find(X) -> where x is the element in question, finds the representive of the set of which x is a member of. This determines if two elmenets
       are in the same subset
    2. Union(X,Y) - > Join two subsets into a single set
    3. Union_BY_RANK(X, Y) -> join two sets, the set with the larger height takes precedence
    4. Union_BY_SIZE(X, Y) -> join two sets, the set with the bigger size takes precedence
**/
#define SET_NOT_FOUND -1
// intializes the set with each element being in its own set
void intialize_set(int arr[], size_t n);
// finds the representative of a set, returns -1 if it does not exist
ssize_t find(int arr[], size_t n, size_t x);
ssize_t union_by_rank(int[], size_t, size_t, size_t);
ssize_t union_by_size(int[], size_t, size_t, size_t);
ssize_t union_(int[], size_t, size_t, size_t);