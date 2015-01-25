#ifndef __lecture_ecriture_fichier__
#define __lecture_ecriture_fichier__

int ecrireDansUnFicher(char * parametre[], int nbParams, char * nomFichier);

int lectureLigneFichier(char * nomFichier, int numeroLigne, char * ligneLue);

int supprimerLigneFichier(char * nomFichier, int numeroLigne, int tailleMaxLigne);

void extraitParametres(char * requete, char * parametres[]);

#endif // __lecture_ecriture_fichier
