#ifndef __controlleur__
#define __controlleur__

//Decalare le nombre max de paramètres que peut avoir une reuquete ou une ligne lue.
extern int NOMBRE_MAX_PARAM;

//Variable Globale pour la taille maximale d'une ligne
extern int TAILLE_MAX_LIGNE;

//Ajoute dans le fichier utilisateur.txt l'utilisateur si son identifiant n'existe pas déjà
int creerUtilisateur(char nomFichier[], char * parametres[], int nbParams);

//Regarde si le nom d'utilisateur et le mot de passe indiqué sont conformes
int authentification(char nomFichier[], char utilisateur[], char motDePasse[]);

// extrait les parametres d'une requete en se basant sur les caractères espaces (' ')
int extraitParametres(char requete[], char * parametres[]);

// regarde si un identifiant existe déjà
int isExistant(char nomFichier[], char aComparer[]);

// Formatte le retour des requêtes (transforme le retour (int) en retourClient (char*))
void formatteMessageRetour(int retour, char retourClient[]);

//Ajoute une enchère dans le fichier enchère. Aucune vérification n'est nécessaire, il suffit de créer un identifiant unique
int ajoutEnchere(char nomFichier[], char * parametres[], int nbParams);


#endif
