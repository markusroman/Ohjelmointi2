#include "array_operations.hh"
#include <iostream>
int greatest_v1(int* itemptr, int size) {
    int greatest = 0;
    for (int i = 0 ; i < size ; ++i) {
        if (*itemptr > greatest) {
            greatest = *itemptr;
        }
        ++itemptr;
    }
    return greatest;
}
int greatest_v2(int* itemptr, int* endptr) {
    int greatest = 0;
    for ( ; itemptr < endptr ; ++itemptr) {
        if (*itemptr > greatest) {
            greatest = *itemptr;
        }
    }
    return greatest;
}
void copy(int* itemptr, int* endptr, int* targetptr) {
    for ( ; itemptr < endptr ; ++itemptr) {
        *targetptr = *itemptr;
        ++targetptr;
    }
}
void reverse(int* leftptr, int* rightptr) {
    --rightptr;
    while ( leftptr != rightptr && (leftptr) + 1 != rightptr ) {
        int tmp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = tmp;
        ++leftptr;
        --rightptr;
    }
}
