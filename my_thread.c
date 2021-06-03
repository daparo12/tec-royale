
#include "my_thread.h"
#include "my_sched.h"
#include "my_mutex.h"





void run_threads(){
    thread_actual = &threads[0];
    setcontext(&threads[0]);  //ejectutar los hilos creados
}



void my_thread_end(){

		//Finaliza o "mata" un hilo y cambia de scheduler.

		hilos_terminados[context_actual] = 1; //Se marca con un 1, representa un thread muerto
    total_tiquetes-=tiquetes[context_actual];
    threads_activos_aux--;

    change_sched();

}


void my_thread_yield(){
	//Cede el procesador mediante la función de cambiar sched.
	change_sched();
}

static void execute_exit_context(){

		//Cede el procesador al terminal los hilos.
    hilos_terminados[context_actual] = 1;
    total_tiquetes -= tiquetes[context_actual];
    threads_activos_aux--;

    change_sched();

    while(1);
}

static void set_exit_context() {

	//Create context for exit_context function
	static int exit_context_created;
    if(!exit_context_created){

        getcontext(&exit_context);

				// Revisar ejemplos de https://pubs.opengroup.org/onlinepubs/009695399/functions/makecontext.html
        exit_context.uc_link = 0;
        exit_context.uc_stack.ss_sp = malloc(TAM_STACK);
        exit_context.uc_stack.ss_size = TAM_STACK;
        exit_context.uc_stack.ss_flags= 0;

        makecontext(&exit_context, (void (*) (void))&execute_exit_context, 0);

        exit_context_created = 1;
    }
}



void my_thread_join(ucontext_t *thread_activo,ucontext_t *thread_en_espera){

		//Inicia cola de espera para un hilo.
		//Recibe hilo actual y un hilo en espera.

		thread_activo -> uc_link = thread_en_espera;
}


void my_thread_detach(ucontext_t *thread_to_detach){

		//Recibe el hilo al que se le quiere dar independencia.
		//Separa el hilo de ejecución del objeto hilo,
		//lo que permite que la ejecución continúe de forma independiente.
		setcontext(thread_to_detach);
		free(thread_to_detach);

}

void my_thread_create(void (*thread_function) (), void *args, int tiquetes_s, int priority_s, int sched){

		//Recibe la función a ejecutar, los argumentos de esa funcion, los tiquetes para el sorteo y la prioridad


		if (!init) {
			int i;

			//Set thread context
			for(i = 0; i < NUM_THREADS; i++) hilos_terminados[i] = 0; //Inicializar el array de threads muertos

			global_current_sched = sched;
			set_exit_context();
			struct itimerval it; //Para quantum

			//sigaltstack () permite que un proceso defina una nueva pila de señales
			//alternativa y /o recupere el estado de una pila de señales alternativa existente.

			signal_stack = malloc(TAM_STACK);

			it.it_interval.tv_sec = 0;
			it.it_interval.tv_usec = INTERVAL * 1000; // Time in millis para el intervalo de ejecución
			it.it_value = it.it_interval; // Se asigna el valor

			setitimer(ITIMER_REAL, &it, NULL);

			struct sigaction act;
			//https://man7.org/linux/man-pages/man2/sigaction.2.html
			act.sa_sigaction = change_sched;

			sigemptyset(&act.sa_mask);
			act.sa_flags = SA_RESTART | SA_SIGINFO;

			sigemptyset(&set);

			sigaddset(&set, SIGALRM);

			sigaction(SIGALRM, &act, NULL);
			init++;
		}

		void *stack; // para utilizar context

		// Crea objeto tipo context
		ucontext_t *thread = &threads[threads_activos];
    getcontext(thread);

    // Asigna memoria a context
    stack = malloc(TAM_STACK);

    // Asigna valores por defecto
    thread -> uc_stack.ss_sp = stack;
    thread -> uc_stack.ss_size = TAM_STACK;
    thread -> uc_stack.ss_flags = 0;
    thread -> uc_link = &exit_context;

    // Inicializa y vacia un signal set
    sigemptyset(&thread -> uc_sigmask);

    // Se manda la funcion al context
    makecontext(thread,(void (*)(void))thread_function, 1, args);


    tiquetes[threads_activos] = tiquetes_s;
    priority[threads_activos] = priority_s;
    total_tiquetes += tiquetes_s;
    threads_activos++;
    threads_activos_aux++;

}
