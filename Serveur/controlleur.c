#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_ecriture_fichier.h"
#include "controlleur.h"

int TAILLE_MAX_LIGNE = 500;
int NOMBRE_MAX_PARAM = 20;


int creerUtilisateur(char nomFichier[], char * parametres[], int nbParams){
    if(isExistant(nomFichier, parametres[1]) == 1){
        return 5;
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
    int i = 1;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * parametres[NOMBRE_MAX_PARAM];

    while (isIdFound == 0 && lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        extraitParametres(ligneLue, parametres);
        if(strcmp(utilisateur, parametres[0]) == 0){
            isIdFound = 1;
            if(strcmp(motDePasse, parametres[1]) == 0){
                return *parametres[2] + 3; //La connexion s'est bien passée on renvoit le type de compte + 3
            }
            return 1;//Le mot de passe est incorrect
        }
        i++;
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

void formatteMessageRetour(int retour, char retourClient[]){
    retourClient[0] = (char) retour + '0';
    retourClient[1] = '\n';
    retourClient[2] = '\0';
}

int ajoutEnchere(char nomFichier[], char * parametres[], int nbParams){
    int i;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char buffer[TAILLE_MAX_LIGNE + 1];
    char * paramLigneLue[20];

    for(i = 0; i< nbParams; i++){
        parametres[nbParams - i] = (char*) malloc(strlen(parametres[nbParams- (i+1)]));
        strcpy(parametres[nbParams - i], parametres[nbParams - (i+1)]); //Il y a assez de place disponible pour décaler les paramètres
    }
    nbParams ++; // On a rajouté un identifiant dans les paramètres

    i = 1;

    while(lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        // On remplace le premier paramètre (le numéro de la requete) par le nouvel identifiant de l'enchère (le numéro de l'enchère précédent + 1)
        extraitParametres(ligneLue, paramLigneLue);
        sprintf(buffer, "%d",atoi(paramLigneLue[0]) + 1);
        strcpy(parametres[1], buffer);
        i++;
    }

    //Si c'est la première enchère
    if(i == 1)
        strcpy(parametres[1], "0");

    ecrireDansUnFicher(nomFichier, parametres, nbParams);

    return 0;

}
