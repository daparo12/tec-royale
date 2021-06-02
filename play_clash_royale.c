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
   char *warrior_level_char = (char *) malloc(sizeof(char)+1);
   warrior_level_char = figure->ascii_item[1];
   char *warrior_level = warrior_level_char[1];
   //printf("%c", a );




   figure->posicion_actual_x = figure->posicion_inicial_x;
   figure->posicion_actual_y = figure->posicion_inicial_y;

   if(figure -> posicion_inicial_x > configuration->canvas_l/2 ){ //Significa que el guerrero es del p2



     while(figure -> posicion_actual_x > 5 ) {
       int ch = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x) & A_CHARTEXT;
       //printf("%d\n",ch);

       if(ch == 124){

         int front_warrior_level = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x-4) & A_CHARTEXT;
         break;
         //int ch = mvwinch(configuration -> canvas, figure->posicion_actual_y-2,figure->posicion_actual_x) & A_CHARTEXT;

       }



        //Limpia la posición anterior
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+5, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x , " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x," ");

       //mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+1, "Y");

       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x+5, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x,  " ");
       //Actualiza
       wrefresh(configuration-> canvas);
       //Mueve una vez
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, figure->ascii_item[0]);
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, figure-> ascii_item[1]);
       figure->posicion_actual_x = figure->posicion_actual_x - 1;
       wrefresh(configuration-> canvas);
       usleep(100000);
     }

   }

   else{ //guerrero del p1
     while(figure -> posicion_actual_x < 134 ) {
       int ch = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x+4) & A_CHARTEXT;
       //printf("a: %d\n ",ch);

       if(ch == 124){

         break;
         //int ch = mvwinch(configuration -> canvas, figure->posicion_actual_y-2,figure->posicion_actual_x) & A_CHARTEXT;

       }


       //Limpia la posición anterior
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x-1, " ");
       //mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x+5, "x"); AQUI ES EL FRENTE
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, " ");
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x-1," ");




       //Actualiza
       wrefresh(configuration-> canvas);

       //Mueve una vez
       mvwprintw(configuration -> canvas,figure->posicion_actual_y,figure -> posicion_actual_x, figure->ascii_item[0]);
       mvwprintw(configuration -> canvas,figure->posicion_actual_y+1,figure -> posicion_actual_x, figure-> ascii_item[1]);
       figure->posicion_actual_x = figure->posicion_actual_x + 1;
       wrefresh(configuration-> canvas);
       usleep(100000);
     }
 }


   figure -> posicion_actual_x = figure -> posicion_inicial_x;
   figure -> posicion_actual_y = figure -> posicion_inicial_y;

   wrefresh(configuration-> canvas);
   //usleep(800000);
}
