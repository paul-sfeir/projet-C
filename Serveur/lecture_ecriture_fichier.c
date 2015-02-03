#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controlleur.h"

#define ERREUR_OUVERTURE -1
#define ERREUR_ECRITURE_FICH -2
#define ERREUR_LECTURE_BUFFER -3
#define ERREUR_ECRITURE_BUFFER -4
#define ERREUR_LECTURE_FICH -5

#define TAILLE_MAX_LIGNE 500


int ecrireDansUnFicher(char nomFichier[], char * parametre[], int nbParams)
{
    FILE * fichier;
    char parametreFormate[TAILLE_MAX_LIGNE];
    int i;
    for(i=0;i<nbParams;i++)
    {
        strcat(parametreFormate, parametre[i]);

        //Si c'est le dernier paramètre, on ne souhaite pas avoir d'espace après.
        if(i != nbParams - 1){
            strcat(parametreFormate, " ");
        }
    }
    strcat(parametreFormate, "\n");

    fichier=fopen(nomFichier,"a");
    if (fichier == NULL)
    {
        return ERREUR_OUVERTURE;
    }

    if (fputs (parametreFormate, fichier) == EOF)
    {
        return ERREUR_ECRITURE_FICH;
    }

    fclose(fichier);

    return 0;
}

int lectureLigneFichier(char nomFichier[], int numeroLigne, char ligneLue[]){
    FILE * fichier;
    int i;

    fichier = fopen(nomFichier, "r");

    if(fichier == NULL){
        return ERREUR_OUVERTURE;
    }

    for(i = 0; i < numeroLigne; i++){
        //Si le numéro de ligne est supérieur à ce qu'il y a dans le fichier
        if(fgets(ligneLue, TAILLE_MAX_LIGNE, fichier) == NULL){
            return -1;
        }
    }

    fclose(fichier);

    //enlève "\n" de la chaine lue
    ligneLue[strlen(ligneLue) - 1] = '\0';

    return 0;

}

int isExistant(char nomFichier[], char aComparer[]){

    FILE *f;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * parametres[20]; // max 20 parametres
    int isExistant = 0; // 0 = false

    f = fopen(nomFichier, "r");

    if(f == NULL){
        return ERREUR_OUVERTURE;
    }

    while(isExistant == 0 || fgets(ligneLue, sizeof ligneLue, f) != NULL){
        extraitParametres(ligneLue, parametres);
        if(strcmp(aComparer, parametres[0])){
            isExistant = 1;
        }
    }

    return isExistant;
}

int supprimerLigneFichier(char nomFichier[], int numeroLigne, int tailleMaxLigne){

    FILE * fIn;
    FILE * fOut;
    int i = 1; //Numéro de ligne commançant à 1
    char nomTemp[100];
    char ligneLue[tailleMaxLigne + 1];

    fIn = fopen(nomFichier, "r");

    if(fIn == NULL){
        return ERREUR_OUVERTURE;
    }

    strcpy(nomTemp, nomFichier);
    strcat(nomTemp, ".temp");

    fOut = fopen(nomTemp, "w");

    if(fOut == NULL){
        fclose(fIn);
        return ERREUR_OUVERTURE;
    }

    while (fgets(ligneLue, sizeof ligneLue, fIn) != NULL)
    {
        if (i != numeroLigne){
            fputs(ligneLue, fOut);
        }
        i++;
    }

    fclose(fIn);
    fclose(fOut);

    remove(nomFichier);
    rename(nomTemp, nomFichier);

    return 0;
}
