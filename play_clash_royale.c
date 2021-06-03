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


void game_lock(){

  mutex_init(&fieldLock);
}



void move_warriors(void *arg){


   mutex_lock(&fieldLock);
   int tiempo_ini = 0;
   int tiempo_fin = 10;
   mutex_unlock(&fieldLock);

   mutex_lock(&fieldLock);
   warrior_props *figure = (warrior_props *) arg;
   mutex_unlock(&fieldLock);

   mutex_lock(&fieldLock);
   char *warrior_level_char = (char *) malloc(sizeof(char)+1);
   warrior_level_char = figure->ascii_item[1];
   char *warrior_level = warrior_level_char[1];
   //printf("%c", a );
   mutex_unlock(&fieldLock);



   mutex_lock(&fieldLock);
   int ch;
   int front_warrior_level;
   int current_warrior_level;
   figure->posicion_actual_x = figure->posicion_inicial_x;
   figure->posicion_actual_y = figure->posicion_inicial_y;
   mutex_unlock(&fieldLock);


   if(figure -> posicion_inicial_x > configuration->canvas_l/2 ){ //Significa que el guerrero es del p2

     while(figure -> posicion_actual_x > 13 ) {
       mutex_lock(&fieldLock);
       ch = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x) & A_CHARTEXT;
       mutex_unlock(&fieldLock);
       if(ch == 124){

         mutex_lock(&fieldLock);
         front_warrior_level = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x-3) & A_CHARTEXT; //Funcional
         current_warrior_level = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x+4) & A_CHARTEXT; //Funcional
         mutex_unlock(&fieldLock);
         //printf("%d b> \n", front_warrior_level);

         if(front_warrior_level > current_warrior_level){

           //printf("p2 won");
           mutex_lock(&fieldLock);
           figure->ascii_item[0] = "  ";
           figure->ascii_item[1] = "  ";
           mutex_unlock(&fieldLock);

           break;
         }

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

       mutex_lock(&fieldLock);
       figure->posicion_actual_x = figure->posicion_actual_x - 1;
       mutex_unlock(&fieldLock);



       wrefresh(configuration-> canvas);
       usleep(100000);
     }

     if(figure -> posicion_actual_x == 13){
       erase();
       mvwprintw(configuration -> canvas,30,10, "Gana el jugador 2");
       usleep(99999999999999999999);
     }


   }

   else{ //guerrero del p1
     while(figure -> posicion_actual_x < 130 ) {
       mutex_lock(&fieldLock);
       ch = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x+4) & A_CHARTEXT;
       mutex_unlock(&fieldLock);

       if(ch == 124){
         mutex_lock(&fieldLock);

         front_warrior_level = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x+5) & A_CHARTEXT; //ESTA MAL
         current_warrior_level = mvwinch(configuration -> canvas, figure->posicion_actual_y+1,figure->posicion_actual_x) & A_CHARTEXT; //Funcional
         //mvwprintw(configuration -> canvas,figure->posicion_actual_y+4,figure -> posicion_actual_x, "front_warrior_level");
         //printf("%d a>", front_warrior_level);
         mutex_unlock(&fieldLock);

         if(front_warrior_level > current_warrior_level){

           mutex_lock(&fieldLock);
           figure->ascii_item[0] = " ";
           figure->ascii_item[1] = " ";
           mutex_unlock(&fieldLock);

           break;
         }

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

       mutex_lock(&fieldLock);
       figure->posicion_actual_x = figure->posicion_actual_x + 1;
       mutex_unlock(&fieldLock);

       wrefresh(configuration-> canvas);
       usleep(100000);
     }
     if(figure -> posicion_actual_x == 130){
       erase();
       mvwprintw(configuration -> canvas,30,10, "Gana el jugador 1");
       usleep(99999999999999999999);
     }




 }

   mutex_lock(&fieldLock);
   figure -> posicion_actual_x = figure -> posicion_inicial_x;
   figure -> posicion_actual_y = figure -> posicion_inicial_y;
   mutex_unlock(&fieldLock);

   wrefresh(configuration-> canvas);
   //usleep(800000);
}
