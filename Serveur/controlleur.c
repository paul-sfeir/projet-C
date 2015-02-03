#include <stdio.h>
#include <stdlib.h>
#include "lecture_ecriture_fichier.h"

int creerUtilisateur(char * parametres[], int nbParams){
    if(isExistant("utilisateur.txt", parametres[0]) == 1){
        return 2;
    }

    ecrireDansUnFicher("utilisateur.txt", parametres, nbParams);

    return 0;
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
    return i;
}
