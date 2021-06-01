
#include <stdio.h>
#include <stdlib.h>
#include "my_thread.h"
#include "my_sched.h"
config *configuration;

void myturn(void *x){
	int **params = x;
  int *number = params[0];
	int a = 0;
	int b = 3;
	while(a<4){

		sleep(1);
		printf("Hi \n");
		a++;
	}
}



int main() {

	parse_file();
	create_canvas();

}
