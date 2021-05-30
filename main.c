
#include <stdio.h>
#include <stdlib.h>
#include "my_thread.h"
#include "my_sched.h"


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

void myturn2(void *x){
	int **params = x;
  int *number = params[0];
	int a = 0;
	int b = 3;
	while(a<5){

		sleep(1);
		printf("Bye \n");
		a++;
	}
}



int main() {

  int n = 3;
  void *arguments[1];
  arguments[0] = &n;

  my_thread_create(myturn, arguments,5,5);
  my_thread_create(myturn2, arguments,100,100);
  run_threads();

}
