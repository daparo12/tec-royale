
#ifndef my_sched
#define my_sched

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ucontext.h>

int sched_actual;


ucontext_t signal_context;


void sched_sort(); //Scheduler de Sorteo

void real_time_sched(); //Scheduler de Tiempo real
void cambiar_scheduler(int new_sched);
void run_threads();
void round_robin();
void change_sched(); //Crea el context segun el tipo de scheduler


#endif
