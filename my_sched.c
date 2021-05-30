
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "my_thread.h"
#include "my_sched.h"

// Documentar

int switch_sched;

void real_time_sched(){

    //Al menos un thread debe estar activo


    int aux = -100;
    int last = context_actual;
    int i;

    // Tiene la cantidad de threads que estan activos y vivos
    // y valida si hay alguno
    if(threads_activos_aux > 0){

        // Itera hasta encontrar el hilo con mayor prioridad que no haya sido
        // ejecutado
        for (i = 0; i < threads_activos; i++) {

            if(aux < priority[i] && !boolean_dead_threads[i] && !priority_aux[i]){

                context_actual = i;
                aux = priority[i];
            }
        }

        if(aux == -1){

            for (i = 0; i < threads_activos; i++) {

                priority_aux[i] = 0;
            }

            real_time_sched();

        }
        else{
            priority_aux[context_actual] = 1; //Actualiza a ejecutado
            thread_actual = &threads[context_actual];

            setcontext(thread_actual);
        }
    }


}


void round_robin(){


    //R: AL menos un thread debe estar activo
    if(threads_activos_aux > 0){

        context_actual = (context_actual + 1); // Cambia al siguiente context

        // Verificar si el thread sigue vivo
        if(boolean_dead_threads[context_actual% threads_activos]){

            // Sigue revisando la lista hasta que encuentre un thread vivo
            while(boolean_dead_threads[context_actual% threads_activos]){
                context_actual+=1;
            }
        }

        // Se asigna el contexto al thread actual
        context_actual = context_actual % threads_activos;
        thread_actual = &threads[context_actual];

        setcontext(thread_actual); //activa el nuevo hilo
    }
}


void sort_scheduler(){

    //Scehduler sort, utiliza los tickets
    srand(time(NULL));

    int aux;

    // cchek si hay activos
    if(threads_activos_aux > 0){

        int winner = rand()%(total_tickets+1);//Determina el ganador del sorteo
        aux = winner;
        int i;

        for (i = 0; i < threads_activos; i++) {

            aux -= tickets[i];

            if(aux<=0){
                if(boolean_dead_threads[i% threads_activos]){
                    while(boolean_dead_threads[i% threads_activos]){
                        i+=1;
                    }
                }

                context_actual = i;
                thread_actual = &threads[context_actual];
                break;
            }

            else{

                tickets[i]++;
                total_tickets++;
            }
        }
        setcontext(thread_actual);//Llama al nuevo hilo
    }


}

void cambiar_scheduler(int change_sched_to){

    //ESta funcion se encarga de cambiar el scheduler

    if(change_sched_to == 0){
      sched_actual = 0;
    }

    if(change_sched_to == 1){
     sched_actual = 1;
     }

    if(change_sched_to == 2){
       sched_actual = 2;
    }
}

void sched_alternator(){

    //Cambia el scheduler actual

    getcontext(&signal_context);

    signal_context.uc_stack.ss_sp = signal_stack;  //Se iguala al stack creado en thread.c
    signal_context.uc_stack.ss_size = TAM_STACK;
    signal_context.uc_stack.ss_flags = 0;

    sigemptyset(&signal_context.uc_sigmask);

    switch_sched = 0;

    // Alterna el valor de sched_actual
    switch_sched = switch_sched^sched_actual;

    // Se envia el valor del nuevo algoritmo de scheduling a utilizar
    cambiar_scheduler(switch_sched);

    if(sched_actual == 0){
      makecontext(&signal_context, round_robin, 1);
    }

    if(sched_actual == 1){
      makecontext(&signal_context, sort_scheduler, 1);
    }

    if(sched_actual == 2){
      makecontext(&signal_context, real_time_sched, 1);
    }

    swapcontext(thread_actual,&signal_context); //Llama a swapcontext de ucontext.h

}
