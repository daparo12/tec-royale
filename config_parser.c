#include "my_thread.h"

int parse_file(const char * file) {

	FILE *ptofile = fopen(file , "r");

	int line = 0;

	char input[64];

	configuration = (config *) malloc(sizeof(config));
	configuration->canvas_h = atoi(fgets(input, 64, ptofile));
	configuration->canvas_l = atoi(fgets(input, 64, ptofile));
  //printf("%d\n",configuration->canvas_l);

  if(strcmp(strtok(fgets(input, 64, ptofile), "\n"), "start") == 0){ }

	int index = 0;

	while(1){
    fgets(input,64,ptofile);
		if(strcmp(strtok(input, "\n"), "fin") == 0){
			break;
		}else if(strcmp(strtok(input, "\n"), "-") == 0){
			continue;
		}

		else{

			warrior_props *tmp_item = (warrior_props *) malloc(sizeof(warrior_props));
      tmp_item->scheduler = atoi(strtok(fgets(input, 64, ptofile), "\n"));


			for(int i = 0; i<2; i++){
				tmp_item->ascii_item[i] = (char *) malloc(sizeof(char)+1);
			}

			strcpy(tmp_item->ascii_item[0], strtok(fgets(input, 64, ptofile), "\n"));
			strcpy(tmp_item->ascii_item[1], strtok(fgets(input, 64, ptofile), "\n"));
			tmp_item->posicion_inicial_x = atoi(strtok(fgets(input, 64, ptofile), "/"));
			tmp_item->posicion_inicial_y = atoi(strtok(NULL, "\n"));
			tmp_item->damage = atoi(strtok(fgets(input, 64, ptofile), "/"));
			tmp_item->health = atoi(strtok(NULL, "\n"));
			configuration->warrior_list[index] = (warrior_props *) malloc(sizeof(warrior_props));
			configuration->warrior_list[index] = tmp_item; //Guarda un guerrero en la lista de guerreros de un jugador

			int temp_index = index+1;
			index ++;
		}
	}


	//onfiguration->espacio_entre_objetos = atoi(fgets(input, 64, ptofile));

  printf("Archivo procesado correctamente.\n");
	fclose(ptofile);
	return 0;

}
