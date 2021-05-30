#define my_mutex_h
#include <stdio.h>
#include <unistd.h>

void my_mutex_init(int *lock);
void my_mutex_destroy(int *lock);
void my_mutex_lock(int *lock);
void my_mutex_unlock(int *lock);
void my_mutex_trylock(int *lock);
