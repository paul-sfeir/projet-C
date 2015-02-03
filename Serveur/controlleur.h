#ifndef __controlleur__
#define __controlleur__


//Ajoute dans le fichier utilisateur.txt l'utilisateur si son identifiant n'existe pas déjà
int creerUtilisateur(char * parametres[], int nbParams);


int extraitParametres(char requete[], char * parametres[]);

#endif // __lecture_ecriture_fichier
