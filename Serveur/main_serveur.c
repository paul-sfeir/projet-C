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
    char pseudoUtilisateur[31];

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
                if(retour == 0 ){
                    strcpy(pseudoUtilisateur, parametres[1]);
                }

                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }

                break;

            case 2:
                retour = ajoutEnchere(FICHIER_ENCHERES, parametres, nbParams, pseudoUtilisateur);
                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                break;

            case 3:
                parametres[2][strlen(parametres[2])-1] = '\0'; //On enlève le caractère \n du montant de l'enchère
                retour = encherir(FICHIER_ENCHERES, parametres[1], parametres[2], pseudoUtilisateur);
                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                break;

            case 4:
                parametres[1][strlen(parametres[1])-1] = '\0'; //On enlève le caractère \n du montant de l'enchère
                retour = finirEnchere(FICHIER_ENCHERES, FICHIER_RESULTATS_ENCHERES, parametres[1], pseudoUtilisateur);
                formatteMessageRetour(retour, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                break;

            case 5:
                envoyerContenuFichierTexte(FICHIER_ENCHERES);
                break;

            case 6:
                envoyerResultatEnchere(FICHIER_RESULTATS_ENCHERES, pseudoUtilisateur);
                break;

            case 7:
                envoyerDetailEnchere(FICHIER_ENCHERES, parametres[1]);
                break;

            case 8:
                strcpy(pseudoUtilisateur,"");
                formatteMessageRetour(0, retourClient);
                if(Emission(retourClient)!=1) {
                    printf("Erreur d'emission\n");
                }
                break;

            case 9:
                rechercherEnchere(FICHIER_ENCHERES, FICHIER_RESULTATS_ENCHERES, parametres[1]);
        }

	}

	return 0;
}
