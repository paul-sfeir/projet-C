#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_ecriture_fichier.h"
#include "controlleur.h"

int TAILLE_MAX_LIGNE = 500;
int NOMBRE_MAX_PARAM = 20;


int creerUtilisateur(char nomFichier[], char * parametres[], int nbParams){
    if(isExistant(nomFichier, parametres[1]) == 1){
        return 4;
    }

    ecrireDansUnFicher(nomFichier, parametres, nbParams);

    return 0;
}

int isExistant(char nomFichier[], char aComparer[]){

    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * parametres[NOMBRE_MAX_PARAM];
    int isExistant = 0;
    int i = 1;

    while(isExistant == 0 && lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        extraitParametres(ligneLue, parametres);

        if(strcmp(aComparer, parametres[0]) == 0){
            isExistant = 1;
        }
        i++;
    }

    return isExistant;
}

int authentification(char nomFichier[], char utilisateur[], char motDePasse[]) {
    int isIdFound = 0;
    int i = 0;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * parametres[NOMBRE_MAX_PARAM];

    while (isIdFound == 0 && lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        extraitParametres(ligneLue, parametres);
        if(strcmp(utilisateur, parametres[0]) == 0){
            isIdFound = 1;
            if(strcmp(motDePasse, parametres[1]) == 0){
                return 0; //La connexion s'est bien passée
            }
            else{
                return 1;//Le mot de passe est incorrect
            }
        }
    }

    return 2; // Si l'identifiant n'a pas été trouvé
}

/*
Extrait les parametres et les place dans le tableau de chaine de caractère.
Renvoie le nombre de paramètres extrait
*/
int extraitParametres(char requete[], char * parametres[]){
    int i = 0;

    parametres[0] = strtok(requete, " ");
    i++;

    while(parametres[i-1] != NULL){
        parametres[i] = strtok(NULL, " ");
        i++;
    }
    return i-1; //On ne compte pas le caractère '\n'
}
