#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "controlleur.h"
#include "lecture_ecriture_fichier.h"

#define FICHIERS_UTILISATEURS "comptes_utilisateurs.txt"
#define ENCHERES "encheres.txt"
#define RESULTATS_ENCHERES "resultats_encheres.txt"
#define CATEGORIES "categories.txt"


int main() {
	char *requete = NULL;
	char * parametres[20]; //nombre max de paramètres dans une requête
    int nbParams;
    int retour;
    char retourClient[2];

	Initialisation();
    AttenteClient();

	while(1) {

        requete = Reception();
        if(requete == NULL){
            break;
        }

		nbParams = extraitParametres(requete, parametres);

        switch ((int) parametres[0][0] - '0'){ //transforme en int

            case 0:
                retour = creerUtilisateur(FICHIERS_UTILISATEURS, parametres, nbParams);
                retourClient[0] = (char) retour + '0';
                retourClient[1] = '\n';
                retourClient[2] = '\0';
                    if(Emission(retourClient)!=1) {
                        printf("Erreur d'emission\n");
                    }
                break;

            case 1:
                retour = authentification(FICHIERS_UTILISATEURS, parametres[1], parametres[2]);
                 switch(retour){
                    case 0:
                        printf("Connexion OK");
                        break;

                    case 1:
                        printf("mot de passe invalide\n");
                        break;

                    case 2:
                        printf("identifiants invalide\n");
                        break;
                 }

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
                TerminaisonClient();
                break;

            case 9:
                printf("9\n");
                break;

        }
	}

    Terminaison();

	return 0;
}
