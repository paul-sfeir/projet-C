#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "vue.h"

int main() {
	char *message;
	int nbLigne;
	int i;
	int connecte = 1;

	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

    while(1){

        if(connecte == 1){
            connecte = menuChoixConnexion();
            if(connecte == -1)
                return 0;
        }

        connecte = menuChoixEnchere();


    }


    if(Emission("1 Paul mdp2\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
sleep(1);
     if(Emission("5\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
nbLigne = atoi(message);

    for(i = 0; i < nbLigne; i++){
        message = Reception();
        printf("%s", message);
    }


	Terminaison();

	return 0;
}
