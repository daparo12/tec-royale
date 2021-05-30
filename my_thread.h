
#define my_thread_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/types.h>
#define TAM_STACK 10000
#define NUM_THREADS 1000
#define INTERVAL 150


sigset_t set;
ucontext_t threads[NUM_THREADS];
ucontext_t *thread_actual;
ucontext_t exit_context;
int context_actual;
int init;
int threads_activos;
int threads_activos_aux;
int priority[NUM_THREADS];
int priority_aux[NUM_THREADS];
int tickets[NUM_THREADS];
int total_tickets;
int boolean_dead_threads[NUM_THREADS];

void my_thread_create(void (*thread_function) (), void *args, int tickets, int priority);

void my_thread_end();

void my_thread_yield();

void my_thread_join();

void my_thread_detach();

void run_threads(); 

void *signal_stack;

static void set_exit_context();

void set_thread_context();
