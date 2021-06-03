
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
int tiquetes[NUM_THREADS];
int total_tiquetes;
int hilos_terminados[NUM_THREADS];
int global_current_sched;

void my_thread_create(void (*thread_function) (), void *args, int tiquetes_s, int priority_s, int sched);

void my_thread_end();

void my_thread_yield();

void my_thread_join();

void my_thread_detach();

void run_threads();

void *signal_stack;

/* The monitor information for the animation */
typedef struct warrior_props {

  char *ascii_item[ITEMS_COUNT]; //list of items
  int posicion_actual_x;
  int scheduler;
  int posicion_actual_y;
  int posicion_inicial_x;
  int posicion_inicial_y;
  int damage;
  int health;
  int tiempo_inicial;
  int tiempo_final;
}warrior_props;

typedef struct config {

  warrior_props *warrior_list[ITEMS_COUNT];
  int espacio_entre_objetos;
  int canvas_h;
  int canvas_l;
  WINDOW *canvas;  //monitor id
}config;

void myke_towers();
void game_lock();
void move_warriors(void *arg);
void print_warriors(void *x);
int parse_file();
static void set_exit_context();
extern config *configuration;
void set_thread_context();
