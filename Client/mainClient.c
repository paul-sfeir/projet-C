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

     if(Emission("2 newEnchère description_blabla www.coucou.fr\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    printf("%s\n", message);
    fflush(stdout);
    sleep(1);

    if(Emission("2 newEnchère2 description_blibli www.coucou2.fr\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    printf("%s\n", message);
    fflush(stdout);


	Terminaison();

	return 0;
}
