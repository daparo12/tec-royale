#include <ncurses.h>
#include "my_thread.h"
#include "my_sched.h"
#include <curses.h>

//monitor_info *tmp_monitor;

void create_canvas(){


  monitor_info *tmp_monitor = (monitor_info *) malloc(sizeof(monitor_info));
  printf("%d \n ", tmp_monitor->canvas_l);
  
  /*
  int x = 0, y = 0;

  initscr();

  noecho();

  curs_set(FALSE);

  tmp_monitor -> canvas = newwin(tmp_monitor -> canvas_h,tmp_monitor -> canvas_l, y, x);

  x += tmp_monitor -> canvas_l;

  box(tmp_monitor -> canvas, 0, 0);

  wrefresh(tmp_monitor-> canvas);
  */


}
