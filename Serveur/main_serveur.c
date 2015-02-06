#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "serveur.h"
#include "controlleur.h"
#include "lecture_ecriture_fichier.h"

#define FICHIER_UTILISATEURS "comptes_utilisateurs.txt"
#define FICHIER_ENCHERES "encheres.txt"
#define FICHIER_RESULTATS_ENCHERES "resultats_encheres.txt"
#define FICHIER_CATEGORIES "categories.txt"


int main() {
	char *requete = NULL;
	char * parametres[20]; //nombre max de paramètres dans une requête
    int nbParams;
    int retour;
    char retourClient[2];
    char nomUtilisateur[31];
    int statutUtilisateur;

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
                retour = creerUtilisateur(FICHIER_UTILISATEURS, parametres, nbParams);

                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                break;

            case 1:
                parametres[2][strlen(parametres[2])-1] = '\0'; //On enlève le caractère \n du mot de passe
                retour = authentification(FICHIER_UTILISATEURS, parametres[1], parametres[2]);
                if(retour > 2 ){
                    strcpy(nomUtilisateur, parametres[1]);
                    statutUtilisateur = retour;
                    retour = 0;
                }

                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                if(retour == 0){
                    sleep(1);
                    // On renvoie le statut de l'utilisateur
                    formatteMessageRetour(statutUtilisateur, retourClient);
                    if(Emission(retourClient)!=1) {
                        printf("Erreur d'emission\n");
                    }
                }

                break;

            case 2:
                retour = ajoutEnchere(FICHIER_ENCHERES, parametres, nbParams);
                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
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
        }

	}

	return 0;
}
