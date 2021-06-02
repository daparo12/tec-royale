
#include <stdio.h>
#include <stdlib.h>
#include "my_thread.h"
#include "my_sched.h"
config *configuration;


void clearScreen(){
	for(int i = 0;i<10000;i++){
		printf("\n");
	}
}

int main(int argc, char **argv) {

	const char * file = argv[2];
	int warrior_iterator = 0;
	parse_file(file);
	create_canvas();
	//char *a = (char *) malloc(sizeof(char)+1);
//	a = configuration->warrior_list[0]->ascii_item[1];
	//printf("%c \n", a[1] );
//	printf("%s \n ", configuration->warrior_list[0]->ascii_item[0]);




	while(configuration->warrior_list[warrior_iterator] != NULL){
		my_thread_create(move_warriors, configuration->warrior_list[warrior_iterator] , 5, 5);
		warrior_iterator++;
	}
	game_lock();
	run_threads();
	clear();
	return 0;


}
