#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "controlleur.h"
#include "lecture_ecriture_fichier.h"


int main() {
	char *requete = NULL;
	char * parametres[20]; //nombre max de paramètres dans une requête
	char nomFichier[1024];
    int i, nbParams;


	Initialisation();

	while(1) {

		AttenteClient();
		requete = Reception();

		nbParams = extraitParametres(requete, parametres);

        switch ((int) parametres[0][0] - '0'){ //transforme en int

            case 0:
                creerUtilisateur(parametres, nbParams);

                break;

            case 1:
                printf("1\n");
                break;

            case 2:
                printf("2\n");
                break;

            case 3:
                printf("3\n");
                break;

            case 4:
                printf("4\n");
                break;

            case 5:
                printf("5\n");
                break;

            case 6:
                printf("6\n");
                break;

            case 7:
                printf("7\n");
                break;

            case 8:
                printf("8\n");
                break;

            case 9:
                printf("9\n");
                break;

        }

	}

	return 0;
}
