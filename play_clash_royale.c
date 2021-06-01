#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "my_thread.h"
#include "my_sched.h"
#include "my_mutex.h"


config* configuration;
int fieldLock;

void game_lock(){

  mutex_init(&fieldLock);
}


void move_warriors(void *arg){
   int tiempo_ini = 0;
   int tiempo_fin = 10;

   warrior_props *figure = (warrior_props *) arg;

   figure -> posicion_actual_x = figure -> posicion_inicial_x;
   figure -> posicion_actual_y = figure -> posicion_inicial_y;

   wrefresh(configuration-> canvas);
   usleep(90000000); // Shorter delay between movements
}
