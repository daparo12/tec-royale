
#define my_thread_h
#include<malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/types.h>
#include <string.h>
#include <ncurses.h>
#define TAM_STACK 10000
#define NUM_THREADS 1000
#define INTERVAL 150
#define ITEMS_COUNT 10


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

/* The monitor information for the animation */
typedef struct item_info {

  char *ascii_item[ITEMS_COUNT]; //list of items
  int posicion_actual_x;
  int scheduler;
  int posicion_actual_y;
  int posicion_inicial_x;
  int posicion_inicial_y;
  int posicion_final_x;
  int posicion_final_y;
}item_info;

typedef struct monitor_info {

  WINDOW *canvas;  //monitor id
  int start_canvas_area; //monitor canvas area
  int end_canvas_area;
  int canvas_h;
  int canvas_l;

}monitor_info;


/* Configuration struct  */
typedef struct config {

  item_info *item_list[ITEMS_COUNT];
  int espacio_entre_objetos;
}config;


void my_thread_create(void (*thread_function) (), void *args, int tickets_s, int priority_s);
void print_warriors(void *x);
int parse_file();
static void set_exit_context();

extern monitor_info *tmp_monitor;

extern config *configuration;
void set_thread_context();
