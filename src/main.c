#include <stdio.h>
#include "include/sort.h"
#include "include/disjoint_set.h"
#include "include/circular.h"
#include <unistd.h> 
#include "include/log.h"
#include "include/search.h"
#include "include/str.h"
#include <fcntl.h>
#include <unistd.h> 
#define MSGSIZE 16 

char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
int i = 1;

int main() {
    char buf[MSGSIZE];
    int p[2], pid = 0, nbytes;
    if(pipe(p) < 0){
        exit(1);
    }

    if ((pid = fork()) > 0) {
        // Parent Branch
        dup2(p[1], STDOUT_FILENO);
        // close the original pipe file descriptors
        close(p[0]);
        close(p[1]);
        printf("%s", msg1);
        fflush(stdout);
        // close here so not blocked
        close(STDOUT_FILENO);
        // this line is needed so it doesnt hang, all write ends to be closed so read doesnt block forever.
        // this line will wait for the child process to exit
        wait(NULL);
    } else{
        dup2(p[0], STDIN_FILENO);
        // close the original pipe file descriptors
        close(p[0]);
        close(p[1]);
        // loop while theres something being read
        // to esecape this, the parent process must close their stdout, which is pointing to the write end of this pipe
        while ((nbytes = read(STDIN_FILENO, buf, MSGSIZE)) > 0)
            printf("%s\n", buf); 
        if (nbytes != 0) 
            // if return by read is not 0
            exit(2); 
        printf("Finished");
    }
    return 0; 
}


int puts_manually ( char const s[ static 1]) {
    // this works because C strings are null termianted -> 0
    for ( size_t i = 0; s[i]; ++i) {
        if ( fputc(s[i], stdout) == EOF ) return EOF ;
        // fflush(stdout);
        // sleep(2);
    }
    if ( fputc('\n', stdout) == EOF ) return EOF ;
    return 0;
}


// typedef union test test;

// union test {
//     unsigned char val;
//     unsigned short val1;
//     // unsigned char bytes[sizeof(unsigned)];
// };

// int main(void) {
//     // int arr[8] = {1,2,4,4, 4 , 4 , 4,6};
//     // int to_search = 4;
//     // int (*comparator)(void *, void *) = (int (*)(void *, void *))&int_compare;
//     // ssize_t val = binary_search((void*)arr, 8, sizeof(int), (void*)(&to_search), comparator);
//     // debug("%zd", val);
//     // return 0;
//     int test[5];
//     intialize_set(test, 5);
//     union_iterative(test, 5, 0, 1);
//     union_iterative(test, 5, 0, 2);
//     // int rep = find_iterative(test, 5, 0);
//     for(int i = 0; i < 5; i ++) {
//         debug("%d", test[i]);
//     }
//     return 0;
// }

// int main(void) {
//     // double A[5] = {
//     //     [0] = 9.0,
//     //     [1] = 2.9,
//     //     [4] = 3.E+25,
//     //     [3] = .00007,
//     // };

//     // for (size_t i = 0; i < 5; ++i) {
//     //     if (0){
//     //         // printf("element %zu is %g", i, A[i]);
//     //     };
//     // };

//     // int (*comparator)(void *, void *) = (int (*)(void *, void *))&int_compare;
//     // int arr[5] = {4,2,5,6,7};
    
//     // bubble_sort(arr, sizeof(int),6, comparator);
//     // quick_sort(arr, sizeof(int),0, 4, comparator);
//     // for (size_t i = 0; i <= 4; ++i) {
//     //     info("element is %d", arr[i]);
//     // };
//     // puts_manually("HARRIS");
//     // char inbuf[ms]
//     // int x = 1, y = 2;
//     // int* x_ptr = &x;
//     // int* y_ptr = &y;
//     // printf("%d\n", x_ptr);
//     // printf("%p\n", (void*)x_ptr);
//     // test twofold = {
//     //     .val = ((0xAA << ( __CHAR_BIT__ *3) ) |(0xBB << ( __CHAR_BIT__*2) ) |(0xCC << __CHAR_BIT__) |0xDD )
//     // };
//     test twofold = {
//         .val = 'C'
//     };
//     // printf ("size is %d\n", sizeof(unsigned));
//     // printf ("size is %d\n", sizeof(test));

    // int test[3] = {0, 1 , 2};
    // intialize_set(test, 3);
    // intialize_set(test, 3);
    // union_iterative(test, 3, 0, 1);
    // ssize_t val = find(test, 3, 0);
//     printf ("size is %d\n", val);
//     // for ( size_t i = 0; i < sizeof(twofold.bytes) ; ++i)
//     //     printf (" byte [% zu]: 0x%.02 hhX\n", i, twofold . bytes [i]) ;
//     //     printf (" byte [% zu]: 0x%.02 hhX\n", 0, (char*)(&twofold.val));
//     // for ( size_t i = 0; i < sizeof(twofold.bytes) ; ++i)
//     //     printf (" byte [% zu]: 0x%.02 hhX\n", i, (char*)(&twofold.val) + i);


//     circular* c = circular_new(3);
//     circular_append(c, 1);
//     double val_1 = circular_pop(c);
//     circular_append(c, 2);
//     circular_append(c, 3);
//     circular_append(c, 4);
//     // for(size_t i = 0; i < 3; i++){
//     //     debug("%lf", c->buffer[i]);
//     // }
//     // debug("HERE");
//     // c = circular_resize(c, 4);
//     // for(size_t i = 0; i < 4; i++){
//     //     debug("%lf", c->buffer[i]);
//     // }
//     double val_2 = circular_pop(c);
//     double val_3 = circular_pop(c);
//     // debug("%lf", val_1);
//     // debug("%lf", val_2);
//     // debug("%lf", val_3);
//     circular_append(c, 1);
//     circular_append(c, 2);
//     circular_append(c, 3);
//     c = circular_resize(c, 5);
//     // debug("HERE");
//     // for(size_t i = 0; i < 3; i++){
//     //     debug("%lf", c->buffer[i]);
//     // }
//     {
//         extern int i;
//         i = 10;
//         debug("%d", i);
//     }
//     {
//         extern int i;
//         debug("%d", i);
//     }
//     // debug("%d", c->capacity);
//     val_1 = circular_pop(c);
//     val_2 = circular_pop(c);
//     val_3 = circular_pop(c);
//     // debug("%lf", val_1);
//     // debug("%lf", val_2);
//     // debug("%lf", val_3);
// }