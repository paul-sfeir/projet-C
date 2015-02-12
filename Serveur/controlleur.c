#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_ecriture_fichier.h"
#include "controlleur.h"
#include "serveur.h"

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
        if(strcmp(parametres[0], utilisateur) == 0){
            isIdFound = 1;
            if(strcmp(parametres[1], motDePasse) == 0){
                return 0;
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

int ajoutEnchere(char nomFichier[], char * parametres[], int nbParams, char pseudoVendeur[]){
    int i;

    for(i = 0; i< nbParams; i++){
        parametres[nbParams - i] = (char*) malloc(strlen(parametres[nbParams- (i+1)]));
        strcpy(parametres[nbParams - i], parametres[nbParams - (i+1)]); //Il y a assez de place disponible pour décaler les paramètres
    }
    nbParams ++; // On a rajouté un identifiant dans les paramètres

    parametres[nbParams - 1][strlen(parametres[nbParams - 1])-1] = '\0'; // On enlève l''\n'.
    parametres[nbParams] = (char*) malloc(strlen(pseudoVendeur)+2); //Pour l''\n' et l''\0'.
    strcpy(parametres[nbParams], pseudoVendeur);
    strcat(parametres[nbParams], "\n\0");
    nbParams ++;

    strcpy(parametres[1], creerNouvelId(nomFichier));

    ecrireDansUnFicher(nomFichier, parametres, nbParams);

    return 0;

}

int encherir(char nomFichier[], char identifiantEnchere[], char montantEnchere[], char pseudoAcheteur[]){
    int i = 1;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * parametres[NOMBRE_MAX_PARAM];
    parametres[9] = NULL; //Sert à tester la présence d'un acheteur
    int nbParams; // Il y a 10 chaines de caractères dans les enchères

    while (lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        nbParams = extraitParametres(ligneLue, parametres);
        if (strcmp(parametres[0], identifiantEnchere) == 0){
            // Si le montant proposé est plus grand que celui de base, on met à jour l'enhère.
            if(atoi(parametres[4]) < atoi(montantEnchere)){
                parametres[4] = (char*) malloc(sizeof(char) * strlen(montantEnchere));
                strcpy(parametres[4], montantEnchere);

                if(parametres[9] == NULL){
                    parametres[nbParams-1][strlen(parametres[nbParams-1]) - 1] = '\0'; //S'il n'y a pas encore d'acheteur, on enlève l''\n' après le nom du vendeur
                }
                else{
                    parametres[nbParams][strlen(parametres[nbParams]) - 1] = '\0';
                }

                parametres[9] = (char*) malloc( sizeof(char) * strlen(pseudoAcheteur) + 2);
                strcpy(parametres[9], pseudoAcheteur);
                nbParams ++;

                supprimerLigneFichier(nomFichier, i, TAILLE_MAX_LIGNE);

                for(i = 0; i< nbParams; i++){
                    parametres[nbParams - i] = (char*) malloc(strlen(parametres[nbParams- (i+1)]));
                    strcpy(parametres[nbParams - i], parametres[nbParams - (i+1)]); //Il y a assez de place disponible pour décaler les paramètres
                }

                strcat(parametres[nbParams],"\n");
                nbParams ++; // On a rajouté un identifiant dans les paramètres

                ecrireDansUnFicher(nomFichier, parametres, nbParams);
                return 0;
            }
            else{
                return 4; //Montant enchère invalide
            }
        }
        i++;
    }
    return 3;
}

char * creerNouvelId(char nomFichier[]){
    int i = 1;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * maxFound;
    char * paramLigneLue[20];

    maxFound = (char*) malloc(10 * sizeof(char)); //Enchère max = 999999999
    strcpy(maxFound, "0");

    while(lectureLigneFichier(nomFichier, i, ligneLue) != -1){
        // On remplace le premier paramètre (le numéro de la requete) par le nouvel identifiant de l'enchère (le numéro de l'enchère précédent + 1)
        extraitParametres(ligneLue, paramLigneLue);

        if(atoi(maxFound) <= atoi(paramLigneLue[0])){
            sprintf(maxFound, "%d",atoi(paramLigneLue[0]) + 1);
        }

        i++;
    }

    return maxFound;
}

int finirEnchere(char nomFichierEncheres[], char nomFichierEncheresTerminees[], char idEnchereATerminee[], char pseudoUtilisateur[]){
    int i = 1;
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * paramLigneLue[20];
    int nbParams = 0;

    while(lectureLigneFichier(nomFichierEncheres, i, ligneLue) != -1){
        // On remplace le premier paramètre (le numéro de la requete) par le nouvel identifiant de l'enchère (le numéro de l'enchère précédent + 1)
        nbParams = extraitParametres(ligneLue, paramLigneLue);

        if(strcmp(idEnchereATerminee, paramLigneLue[0]) == 0){
            if (strcmp(pseudoUtilisateur, paramLigneLue[8]) != 0 ){
                return 6;
            }
            supprimerLigneFichier(nomFichierEncheres, i, TAILLE_MAX_LIGNE);

            printf("%s\n", paramLigneLue[0]);

            for(i = 0; i< nbParams; i++){
                paramLigneLue[nbParams - i] = (char*) malloc(strlen(paramLigneLue[nbParams- (i+1)]));
                strcpy(paramLigneLue[nbParams - i], paramLigneLue[nbParams - (i+1)]); //Il y a assez de place disponible pour décaler les paramètres
            }

            nbParams ++; // On a rajouté un identifiant dans les paramètres
            ecrireDansUnFicher(nomFichierEncheresTerminees, paramLigneLue, nbParams);
            return 0;
        }

        i++;
    }

    return -1;

}

void envoyerResultatEnchere(char nomFichierEncheresTerminees[], char pseudoUtilisateur[]){
    int i = 1;
    int j = 0;
    char buffer[TAILLE_MAX_LIGNE + 1];
    char ligneLue[TAILLE_MAX_LIGNE + 1];

    char * paramLigneLue[20];
    char requete[15];

    paramLigneLue[9] = NULL;

     while(lectureLigneFichier(nomFichierEncheresTerminees, i, ligneLue) != -1){
        extraitParametres(ligneLue, paramLigneLue);
        if(paramLigneLue[0][0] == '\n')
            break;
        if(paramLigneLue[9] != NULL){
            paramLigneLue[9][strlen(paramLigneLue[9]) -1] = '\0';
            if(strcmp(paramLigneLue[9], pseudoUtilisateur) == 0){
                j++;
            }
            else if(strcmp(paramLigneLue[8], pseudoUtilisateur) == 0){
                j++;
            }
        }
        else{
            paramLigneLue[8][strlen(paramLigneLue[8]) -1] = '\0';
            if(strcmp(paramLigneLue[8], pseudoUtilisateur) == 0){
                j++;
            }
        }
        paramLigneLue[9] = NULL;

        i++;
     }
     //précise le nombre de ligne allant être envoyé.
        sprintf(requete, "%d", j);
        printf("%d\n", j);
        strcat(requete, "\n");
        Emission(requete);

        i = 1;

    while(lectureLigneFichier(nomFichierEncheresTerminees, i, ligneLue) != -1){

        extraitParametres(ligneLue, paramLigneLue);
        if(paramLigneLue[0][0] == '\n')
            break;
        strcpy(buffer, paramLigneLue[0]);
        strcat(buffer, "\t\t");
        strcat(buffer, paramLigneLue[1]);
        strcat(buffer, "\t\t");
        strcat(buffer, paramLigneLue[4]);
        strcat(buffer, "\t\t");
        strcat(buffer, paramLigneLue[6]);
        strcat(buffer, "\t\t");
        strcat(buffer, paramLigneLue[8]);


        if(paramLigneLue[9] != NULL){
            strcat(buffer, "\t\t");
            strcat(buffer, paramLigneLue[9]);
            paramLigneLue[9][strlen(paramLigneLue[9]) -1] = '\0';
            if(strcmp(paramLigneLue[9], pseudoUtilisateur) == 0){
                Emission(buffer);
            }
            else if(strcmp(paramLigneLue[8], pseudoUtilisateur) == 0){
                Emission(buffer);
            }
        }
        else{
            paramLigneLue[8][strlen(paramLigneLue[8]) -1] = '\0';
            if(strcmp(paramLigneLue[8], pseudoUtilisateur) == 0){
                Emission(buffer);
            }
        }
        paramLigneLue[9] = NULL;

        i++;
     }
}

void envoyerDetailEnchere(char nomFichier[], char numeroEnchere[]){
    int i = 1;
    char buffer[4096];
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * paramLigneLue[20];
    int nbParams;

     while(lectureLigneFichier(nomFichier, i, ligneLue) != -1){
         strcpy(buffer, ligneLue);
        nbParams = extraitParametres(ligneLue, paramLigneLue);
        if(strcmp(paramLigneLue[0], numeroEnchere) == 0){
            strcpy(buffer, paramLigneLue[0]);
            for(i=1;i < nbParams; i++){
                strcat(buffer, "\t");
                strcat(buffer, paramLigneLue[i]);
            }
            strcat(buffer, "\n");

           Emission(buffer);
        }
        i++;
     }
}

void rechercherEnchere(char nomFichierEncheres[], char nomFichierEncheresTerminees[], char nomARechercher[]){
    int i = 1;
    int j = 0;
    char * occurences[50];
    char buffer[4096];
    char ligneLue[TAILLE_MAX_LIGNE + 1];
    char * paramLigneLue[20];
    int nbParams;

    nomARechercher[strlen(nomARechercher) - 1] = '\0'; // On enlève le caractère '\n'

     while(lectureLigneFichier(nomFichierEncheres, i, ligneLue) != -1){

        nbParams = extraitParametres(ligneLue, paramLigneLue);

        if(findIfPresent(paramLigneLue[1], nomARechercher) == 0){
            strcpy(buffer, paramLigneLue[0]);
            for(i=1;i < nbParams; i++){
                strcat(buffer, "\t");
                strcat(buffer, paramLigneLue[i]);
            }
            strcat(buffer, "\n");

            occurences[j] = (char*) malloc (sizeof(buffer));
            strcpy(occurences[j], buffer);
            j++;
        }
        i++;
     }

    i=1;
     while(lectureLigneFichier(nomFichierEncheresTerminees, i, ligneLue) != -1){
        strcpy(buffer, ligneLue);
        extraitParametres(ligneLue, paramLigneLue);
        if(findIfPresent(paramLigneLue[1], nomARechercher) == 0){

            strcpy(buffer, paramLigneLue[0]);
            for(i=1;i < nbParams; i++){
                strcat(buffer, "\t");
                strcat(buffer, paramLigneLue[i]);
            }
            strcat(buffer, "\n");

            occurences[j] = (char*) malloc (sizeof(buffer));
            strcpy(occurences[j], buffer);
            j++;
        }
        i++;
     }

    sprintf(buffer, "%d", j);
    strcat(buffer, "\n");
    printf("%s\n", buffer);
    Emission(buffer);
    for(i=0; i< j;i++){
        Emission(occurences[i]);
    }

}

int findIfPresent(char * chaine1, char * chaineAChercher){
    int i = 0;
    int isFound = 1;
    int j, k;

    if(strlen(chaine1) < strlen(chaineAChercher)){
        return 1;
    }

    while(i + strlen(chaineAChercher) <= strlen(chaine1) && isFound == 1){
        j=0;
        k=0;
        while(chaineAChercher[j] == chaine1[i + k] && isFound == 1){
            if(j== strlen(chaineAChercher)){
                isFound = 0;
            }
            j++;
            k++;
        }
        i++;
    }
    return isFound;

}

