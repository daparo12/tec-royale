
#include "my_thread.h"
#include "my_sched.h"

void my_thread_end(){

		//Finaliza o "mata" un hilo y cambia de scheduler.

		boolean_dead_threads[context_actual] = 1;
    total_tickets-=tickets[context_actual];
    threads_activos_aux--;

    sched_alternator();

}


void my_thread_yield(){

	//Cede el procesador mediante la función de cambiar sched.
	sched_alternator();
}

void run_threads(){
    thread_actual = &threads[0];
    setcontext(&threads[0]);  //ejectutar los hilos creados
}

static void execute_exit_context(){

		//Cede el procesador al terminal los hilos.
    boolean_dead_threads[context_actual] = 1;
    total_tickets -= tickets[context_actual];
    threads_activos_aux--;

    sched_alternator();

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

void my_thread_create(void (*thread_function) (), void *args, int tickets_s, int priority_s){

		//Recibe la función a ejecutar, los argumentos de esa funcion, los tickets para el sorteo y la prioridad

		if (!init) {
			int i;

			//Set thread context
			for(i = 0; i < NUM_THREADS; i++) boolean_dead_threads[i] = 0; //Inicializar el array de threads muertos

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
			act.sa_sigaction = sched_alternator;

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

    tickets[threads_activos] = tickets_s;
    priority[threads_activos] = priority_s;
    total_tickets += tickets_s;
    threads_activos++;
    threads_activos_aux++;

}
