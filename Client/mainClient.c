#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

int main() {
	char *message;

	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

     if(Emission("0 Mai mdp Mai Hoang 1 19_Rue_Du_Soleil 0123456789\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    printf("%s\n", message);
    fflush(stdout);
    sleep(1);

    if(Emission("0 Paul mdp2 Paul Sfeir 1 19_Rue_Du_Soleil 0123456789\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    printf("%s\n", message);
    fflush(stdout);


	Terminaison();

	return 0;
}
