#ifndef __lecture_ecriture_fichier__
#define __lecture_ecriture_fichier__

int ecrireDansUnFicher(char nomFichier[], char * parametre[], int nbParams);

int lectureLigneFichier(char nomFichier[], int numeroLigne, char ligneLue[]);

int supprimerLigneFichier(char nomFichier[], int numeroLigne, int tailleMaxLigne);

#endif // __lecture_ecriture_fichier
