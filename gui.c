#include <ncurses.h>
#include "my_thread.h"
#include "my_sched.h"
#include <curses.h>
config* configuration;




char top[10] = {' ','_',' ',' ',' ','|','~',' ',' ','_',' '};
char tow[11] = {'[','_',']','-','-',' ','-','-','[','_',']'};
char windo[11] = {'[','_',']','-','-',' ','-','-','[','_',']'};
char bed[11] = {'[',' ',']',' ','<','^','>',' ','[',' ',']'};
char door[11] = {'[','_',']','_','[','I',']','_','[','_',']'};

void myke_towers(){
  //P1 up
  mvwprintw(configuration -> canvas,1, 1, top);
  mvwprintw(configuration -> canvas,2, 1, tow);
  mvwprintw(configuration -> canvas,3, 1, windo);
  mvwprintw(configuration -> canvas,4, 1, bed);
  mvwprintw(configuration -> canvas,5, 1, door);
  //P1 down
  mvwprintw(configuration -> canvas,configuration->canvas_h-6, 1, top);
  mvwprintw(configuration -> canvas,configuration->canvas_h-5, 1, tow);
  mvwprintw(configuration -> canvas,configuration->canvas_h-4, 1, windo);
  mvwprintw(configuration -> canvas,configuration->canvas_h-3, 1, bed);
  mvwprintw(configuration -> canvas,configuration->canvas_h-2, 1, door);
  //P2 up
  mvwprintw(configuration -> canvas,1, configuration->canvas_l-12, top);
  mvwprintw(configuration -> canvas,2, configuration->canvas_l-12, tow);
  mvwprintw(configuration -> canvas,3, configuration->canvas_l-12, windo);
  mvwprintw(configuration -> canvas,4, configuration->canvas_l-12, bed);
  mvwprintw(configuration -> canvas,5, configuration->canvas_l-12, door);
  //P2 down
  mvwprintw(configuration -> canvas,configuration->canvas_h-6, configuration->canvas_l-12, top);
  mvwprintw(configuration -> canvas,configuration->canvas_h-5, configuration->canvas_l-12, tow);
  mvwprintw(configuration -> canvas,configuration->canvas_h-4, configuration->canvas_l-12, windo);
  mvwprintw(configuration -> canvas,configuration->canvas_h-3, configuration->canvas_l-12, bed);
  mvwprintw(configuration -> canvas,configuration->canvas_h-2, configuration->canvas_l-12, door);
}

void draw_river(){
  int river_layer1 = (configuration->canvas_l/2) - 5;
  int river_layer2 = (configuration->canvas_l/2) + 5;
  int river_end = (configuration->canvas_h-1);
  for(int i=1;i!=river_end;i++){
    mvwprintw(configuration -> canvas,i, river_layer1, "x");
    mvwprintw(configuration -> canvas,i, river_layer2, "x");
  }

}


void draw_bridges(){
  int brige_start = (configuration->canvas_l/2) - 5;
  int bridge_end = (configuration->canvas_l/2) + 5;

  for(int i=brige_start;i!=bridge_end+1;i++){
    mvwprintw(configuration -> canvas,1, i, "-");
    mvwprintw(configuration -> canvas,5, i, "-");

    mvwprintw(configuration -> canvas,configuration->canvas_h-6, i, "-");
    mvwprintw(configuration -> canvas,configuration->canvas_h-2, i, "-");
  }

}

void create_canvas(){

  int x = 0, y = 0;
  initscr();
  noecho();
  curs_set(FALSE);

  configuration -> canvas = newwin(configuration -> canvas_h,configuration -> canvas_l, y, x);
  x += configuration -> canvas_l;
  box(configuration -> canvas, 0, 0);
  wrefresh(configuration-> canvas);
  //printf("%s \n ", configuration->warrior_list[0]->ascii_item[0]);
  myke_towers();
  draw_river();
  draw_bridges();



}
