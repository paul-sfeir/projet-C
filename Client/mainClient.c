#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main() {
	char *message;

	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

    if(Emission("0 paul sfeir\n")!=1) {
        printf("Erreur d'emission\n");
    }
/*
	message = Reception();
	while(message != NULL) {
		printf("%s\n", message);
		free(message);
		message = Reception();
	}
*/

	Terminaison();

	return 0;
}
