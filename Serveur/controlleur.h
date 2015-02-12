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
int ajoutEnchere(char nomFichier[], char * parametres[], int nbParams, char pseudoVendeur[]);

//Enchérit si le montant est supérieur au précédent. Met à jour le nom de l'acheteur
int encherir(char nomFichier[], char identifiantEnchere[], char montantEnchere[], char pseudoUtilisateur[]);

//CHerche dans le fichier le dernier Id présent et renvoie cette valeur + 1
char * creerNouvelId(char nomFichier[]);

//Déplace une enchère dans le fichier enchères terminées (en vérifiant que l'utilisateur correspond)
int finirEnchere(char nomFichierEncheres[], char nomFichierEncheresTerminees[], char idEnchereATerminee[], char pseudoUtilisateur[]);

//Envoie les résultats des enchères si le nom est contenue dans une enchère.
void envoyerResultatEnchere(char nomFichierEncheresTerminees[], char pseudoUtilisateur[]);

//Envoie les détails d'une enchère.
void envoyerDetailEnchere(char nomFichier[], char numeroEnchere[]);

//Recherche dans les enchères le mot à chercher et fais une liste avec toutes les enchères qui corrrpondaient
void rechercherEnchere(char nomFichierEncheres[], char nomFichierEncheresTerminees[], char nomARechercher[]);

//Foncion pour chercher si une chaine est comprise dans une autre
int findIfPresent(char * chaine1, char * chaineAChercher);

#endif
