#include <stdio.h>
#include <stdlib.h>
#include "my_mutex.h"


int acquire_lock(int *lock){

    unsigned int  tmp = 1;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
    return tmp;
}

int set_lock(int *lock){

    return acquire_lock(lock);
}

void mutex_init(int *lock){

    lock = 0;
}

void mutex_destroy(int *lock) {

    free(lock);
}

void mutex_lock(int *lock) {

    while (*lock){
        sleep(1);
    }
    test_and_set(lock);
}

void mutex_unlock(int *lock) {

    unsigned int  tmp = 0;
    __asm__(
        "xchgl %0, %1;\n"
        : "=r"(tmp), "+m"(*lock)
        : "0"(tmp)
        :"memory");
}

void mutex_trylock(int *lock) {

    while (*lock){
        usleep(1000);
    }
    test_and_set(lock);
}
