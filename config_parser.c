#include "my_thread.h"

int parse_file(const char * file) {

	FILE *ptofile = fopen(file , "r");

	int line = 0;

	char input[64];

	configuration = (config *) malloc(sizeof(config));

	configuration->canvas_h = atoi(fgets(input, 64, ptofile));
	configuration->canvas_l = atoi(fgets(input, 64, ptofile));

  if(strcmp(strtok(fgets(input, 64, ptofile), "\n"), "start") == 0){ }

	int index = 0;

	while(1){
    fgets(input,64,ptofile);
		if(strcmp(strtok(input, "\n"), "fin") == 0){
      printf("end \n");
			break;
		}else if(strcmp(strtok(input, "\n"), "-") == 0){
			continue;
		}

		else{

			//item_info *tmp_item = (item_info *) malloc(sizeof(item_info));
      printf("sched: %d \n " ,atoi(strtok(fgets(input, 64, ptofile), "\n")));

      /*
			for(int i = 0; i<2; i++){
				tmp_item->ascii_item[i] = (char *) malloc(sizeof(char)+1);
			}*/


			printf("asci[0]: %s\n ", strtok(fgets(input, 64, ptofile), "\n"));
			printf("asci[1]: %s \n ", strtok(fgets(input, 64, ptofile), "\n"));

			printf("inix: %d\n", atoi(strtok(fgets(input, 64, ptofile), "/")));
			printf("iniy: %d\n", atoi(strtok(NULL, "\n")));
			printf("finx: %d\n", atoi(strtok(fgets(input, 64, ptofile), "/")));
			printf("finy: %d\n ", atoi(strtok(NULL, "\n")));

			//configuration->item_list[index] = (item_info *) malloc(sizeof(item_info));
			//configuration->item_list[index] = tmp_item; //Guarda un guerrero en la lista de guerreros de un jugador

			int temp_index = index+1;

			//my_thread_create(print_warriors,arguments,5,5);
			index ++;
		}
	}

	//onfiguration->espacio_entre_objetos = atoi(fgets(input, 64, ptofile));


	fclose(ptofile);
	return 0;

}
