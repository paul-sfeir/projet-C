#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERREUR_OUVERTURE -1
#define ERREUR_ECRITURE_FICH -2
#define ERREUR_LECTURE_BUFFER -3
#define ERREUR_ECRITURE_BUFFER -4
#define ERREUR_LECTURE_FICH -5

#define TAILLE_MAX_LIGNE 50


int ecrireDansUnFicher(char * parametre[], int nbParams, char * nomFichier)
{
    FILE * fichier;
    char * parametreFormate[5000];
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

int lectureLigneFichier(char * nomFichier, int numeroLigne, char * ligneLue){
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

int supprimerLigneFichier(char * nomFichier, int numeroLigne, int tailleMaxLigne){

    FILE * fIn;
    FILE * fOut;
    int i = 1; //Numéro de ligne commançant à 1
    char * nomTemp;
    char * ligneLue[tailleMaxLigne + 1];

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

int extraitParametres(char * requete, char * parametres[]){



    return 0;
}

int main ()
{
    char * lecture[TAILLE_MAX_LIGNE];
    char * chaine[1];

    char * ch1 = "ligne ";
    char * ch2 = "1";

    chaine[0] = ch1;
    chaine[1] = ch2;
    ecrireDansUnFicher(chaine, 2, "test.txt");

    //      1 = ligne 1
    if(lectureLigneFichier("test.txt", 2, lecture) != 0){
        printf("Probleme lecture");
    }
    else{
        printf("%s", lecture);
    }

    supprimerLigneFichier("test.txt", 4, TAILLE_MAX_LIGNE);

	return 0;
}


