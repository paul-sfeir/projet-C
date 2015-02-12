#ifndef __VUE_H__
#define __VUE_H__

//Pour purger
void purger(void);
void clean (char *chaine);

//affiche le menu avec le chois de connesion
int menuChoixConnexion();

//Demande les identifiants
int menuConnexion();

//Créer un compte
int menuCreationCompte();

//Verifie si une chaine est vide
int isVide(char identifiant[]);

//Menu pour le choix concernant les enchères
int menuChoixEnchere();

//Affiche le message correspondant au retour
void messageRetour(int retour);

//Permet d'ajouter une enchère
void menuAjouterEnchere();

//Enchérit sur une enchère
void encherir();

//Affiche les enchères terminées de l'utilisateur
void encheresTerminees();

//Affiche les enchères en cours
void encheresEnCours();

//Finit une enchère
void finirEnchere();

//Affiche les détails d'une enchère
void detailEnchere();

//Fait une recherche dans les enchères
void rechercherEnchere();

#endif
