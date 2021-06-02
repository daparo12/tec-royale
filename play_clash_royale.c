#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "my_thread.h"
#include "my_sched.h"
#include "my_mutex.h"


config* configuration;
int fieldLock;
time_t t;
/* Intializes random number generator */

void game_lock(){

  mutex_init(&fieldLock);
}


void move_warriors(void *arg){
   int tiempo_ini = 0;
   int tiempo_fin = 10;

   warrior_props *figure = (warrior_props *) arg;
   //char *warrior_level = (char *) malloc(sizeof(char)+1);
   //warrior_level =figure->ascii_item[1];


   figure->posicion_actual_x = figure->posicion_inicial_x;
   figure->posicion_actual_y = figure->posicion_inicial_y;

   if(figure -> posicion_inicial_x > configuration->canvas_l/2 ){ //Significa que el guerrero es del p2



     while(figure -> posicion_actual_x > 12 ) {
       //Limpia la posición anterior
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+6, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+7, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+8, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+9, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+10, " ");
       //mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-1, "Y"); AQUI ES EL FRENTE
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+6, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+7, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+8, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+9, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+10, " ");
       //Actualiza
       wrefresh(configuration-> canvas);
       //Mueve una vez
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, figure->ascii_item[0]);
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, figure-> ascii_item[1]);
       figure->posicion_actual_x = figure->posicion_actual_x - 6;
       wrefresh(configuration-> canvas);
       usleep(700000);
     }

   }

   else{ //guerrero del p1
     while(figure -> posicion_actual_x < 134 ) {

       if(figure -> posicion_actual_x+5 == "|"){ //Se topa un warrior

       }


       //Limpia la posición anterior
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-2, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-3, "x");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-4, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-5, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-6, " ");
       //mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+5, "x"); AQUI ES EL FRENTE
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-2, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-3, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-4, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-5, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-6," ");




       //Actualiza
       wrefresh(configuration-> canvas);

       //Mueve una vez
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, figure->ascii_item[0]);
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, figure-> ascii_item[1]);
       figure->posicion_actual_x = figure->posicion_actual_x + 6;
       wrefresh(configuration-> canvas);
       usleep(700000);
     }
 }


   figure -> posicion_actual_x = figure -> posicion_inicial_x;
   figure -> posicion_actual_y = figure -> posicion_inicial_y;

   wrefresh(configuration-> canvas);
   //usleep(800000);
}
