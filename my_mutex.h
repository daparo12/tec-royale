#define my_mutex_h
#include <stdio.h>
#include <unistd.h>

void mutex_init(int *lock);
void mutex_destroy(int *lock);
void mutex_lock(int *lock);
void mutex_unlock(int *lock);
void mutex_trylock(int *lock);
