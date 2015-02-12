#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vue.h"
#include "client.h"

void purger(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');

    if (p)
    {
        *p = 0;
    }

    else
    {
        purger();
    }
}

int menuChoixConnexion(){
    int choix;
    int retour;

    do{
        do{
            printf("\n\n1- Connexion\n2- Créer un compte\n3-Quitter l'application\nSaisir votre choix: ");
            scanf("%d", &choix);
            purger();
        } while(choix != 1 && choix != 2 && choix != 3);

        if(choix == 1){
            retour = menuConnexion();
            if(retour == 0){
                printf("Vous êtes connecté.\n");
            }
            else{
                messageRetour(retour);
            }
        }
        else{
            if(choix == 2){
                retour = menuCreationCompte();
                if(retour == 0){
                    printf("Le compte a bien été crée.\n\n");
                    retour = 1; // Il ne sort pas tant qu'il n'est pas connecté
                }
                else{
                    printf("Le pseudo est déjà pris\n\n");
                }
            }
            if(choix == 3)
                return -1;

        }

    }while(retour != 0); // Tant que non connecté
    return retour;
}

int menuConnexion(){
    char identifiant[31];
    char motDePasse[31];
    char requete[65];
    char *message;
    int retour;

    do{
        printf("Veuillez saisir votre identifiant : ");
        fgets(identifiant, sizeof(identifiant), stdin);
        clean(identifiant);
        enleverEspace(identifiant);
    }while(isVide(identifiant));

    do{
        printf("Veuillez saisir votre mot de passe : ");
        fgets(motDePasse, sizeof(motDePasse), stdin);
        clean(motDePasse);
        enleverEspace(motDePasse);
    }while(isVide(motDePasse));

    strcpy(requete, "1 ");
    strcat(requete, identifiant);
    strcat(requete, " ");
    strcat(requete, motDePasse);
    strcat(requete, "\n");

    if (Emission(requete) != 1){
        printf("Erreur d'émission \n");
    }

    message = Reception();
    fflush(stdout);

    retour = atoi(message);

    return retour;
}

int menuCreationCompte(){
    char requete[500];
    char identifiant[31];
    char motDePasse[31];
    char nom[31];
    char prenom[31];
    char adresse[101];
    int numeroTel;
    char numTel[11];
    char *message;
    int retour;

        do{
        printf("Veuillez saisir votre identifiant : ");
        fgets(identifiant, sizeof(identifiant), stdin);
        clean(identifiant);
        enleverEspace(identifiant);
    }while(isVide(identifiant));

    do{
        printf("Veuillez saisir votre mot de passe : ");
        fgets(motDePasse, sizeof(motDePasse), stdin);
        clean(motDePasse);
        enleverEspace(motDePasse);
    }while(isVide(motDePasse));

    do{
        printf("Veuillez saisir votre nom : ");
        fgets(nom, sizeof(nom), stdin);
        clean(nom);
        enleverEspace(nom);
    }while(isVide(nom));

    do{
        printf("Veuillez saisir votre prenom: ");
        fgets(prenom, sizeof(prenom), stdin);
        clean(prenom);
        enleverEspace(prenom);
    }while(isVide(prenom));

    do{
        printf("Veuillez saisir votre adresse: ");
        fgets(adresse, sizeof(adresse), stdin);
        clean(adresse);
        enleverEspace(adresse);
    }while(isVide(adresse));

    do{
        printf("Veuillez saisir votre numéro de téléphone: ");
        scanf("%d", &numeroTel);
        purger();
    }while(numeroTel < 0100000000 || numeroTel > 9999999999);

    sprintf(numTel, "%d", numeroTel);

    strcpy(requete, "0 ");
    strcat(requete, identifiant);
    strcat(requete, " ");
    strcat(requete, motDePasse);
    strcat(requete, " ");
    strcat(requete, prenom);
    strcat(requete, " ");
    strcat(requete, nom);
    strcat(requete, " ");
    strcat(requete, adresse);
    strcat(requete, " ");
    strcat(requete, numTel);
    strcat(requete, "\n");

    Emission(requete);
    message = Reception();
    fflush(stdout);

    retour = atoi(message);

    return retour;

}

int isVide(char identifiant[]){
    int i = 0;

    while(identifiant[i] == ' ' && identifiant[i] != '\0'){
        i++;
    }
    if(identifiant[i] != '\0'){
        return 0;
    }
    else{
        return 1;
    }
}

int menuChoixEnchere(){
    int choix;

    do{
        printf("\n\n\n1- Voir les enchères en cours\n");
        printf("2- Ajouter un objet aux enchères\n");
        printf("3- Voir les enchères terminées\n");
        printf("4- Rechercher des enchères\n");
        printf("5- Se déconecter\n");
        printf("Faites votre choix : ");
        scanf("%d", &choix);
        purger();
    }while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5);

    switch(choix){
        case 1:
            encheresEnCours();
            break;

        case 2:
            menuAjouterEnchere();
            break;

        case 3:
            encheresTerminees();
            break;

        case 4:
            rechercherEnchere();
            break;

        case 5:
            Emission("8\n");
            return 1;
            break;
    }
    return 0;
}

void rechercherEnchere(){
    char * message;
    int nbLigne;
    int i;
    char keyWord[50];
    char requete[60];

    do{
        printf("Veuillez saisir un mot clés : ");
        fgets(keyWord, sizeof(keyWord), stdin);
        clean(keyWord);
        enleverEspace(keyWord);
    }while(isVide(keyWord));

    strcpy(requete, "9 ");
    strcat(requete, keyWord);
    strcat(requete, "\n");
    Emission(requete);

    message = Reception();
    nbLigne = atoi(message);

    printf("ID\t\tNom objet\t\tPrix\t\tLieu de Vente\t\tVendeur\t\tAcheteur\n");

    for(i = 0; i < nbLigne; i++){
        message = Reception();
        printf("%s", message);
    }

}

void encheresEnCours(){
    int choix;
    char * message;
    int nbLigne;
    int i;

    if(Emission("5\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    nbLigne = atoi(message);

    printf("ID\t\tNom objet\t\t Prix\n");

    for(i = 0; i < nbLigne; i++){
        message = Reception();
        message[strlen(message) - 1] = '\0';
        printf("%s\n", message);
    }

    do{
        printf("\n\n\n1- Enchérir\n");
        printf("2- Détail Enchère\n");
        printf("3- Finir Enchère\n");
        printf("4- Quitter\n");
        scanf("%d", &choix);
        purger();
   }while(choix != 1 && choix != 2 && choix != 3 && choix != 4);

    switch(choix){
        case 1:
            encherir();
            break;

        case 2:
            detailEnchere();
            break;

        case 3:
            finirEnchere();
            break;

        case 4:
            break;
    }

}

void detailEnchere(){

    char * message;
    char requete[200];
    int idEnchere;
    char buffer[100];

    do{
        printf("Saisir le numéro de l'enchère : ");
        scanf("%d", &idEnchere);
    }while(idEnchere < 0 || idEnchere > 1000);

    strcpy(requete, "7 ");
    sprintf(buffer, "%d", idEnchere);
    strcat(requete, buffer);
    strcat(requete, "\n");

    printf("%s\n", requete);

    if(Emission(requete)!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    printf("ID\tNom\tDescription\tURL\tPrix\tCatégorie\tLieu de vente\t Nom Vendeur\t Nom Acheteur\n");
    printf("%s\n\n\n", message);

}

void encheresTerminees(){
    int choix;
    char * message;
    int i;
    int nbLigne;

    if(Emission("6\n")!=1) {
        printf("Erreur d'emission\n");
    }

    message = Reception();
    nbLigne = atoi(message);

    printf("ID\t\tNom objet\t\tPrix\t\tLieu de Vente\t\tVendeur\t\tAcheteur\n");

    for(i = 0; i < nbLigne; i++){
        message = Reception();
        printf("%s", message);
    }
    do{
        printf("\n\n\n1- Quitter\n");
        scanf("%d", &choix);
        purger();
    }while(choix != 1);

}

void encherir(){

    int idEnchere;
    int montantEnchere;
    char requete[51];
    char buffer[30];
    char * message;
    int retour;

    do{
        printf("Saisir l'enchère pour laquelle vous voulez enchérir : ");
        scanf("%d", &idEnchere);
    }while(idEnchere < 0 || idEnchere > 1000);

    do{
        printf("Saisir le montant de votre enchère : ");
        scanf("%d", &montantEnchere);
    }while(idEnchere < 0 || idEnchere > 100000000);

    strcpy(requete, "3 ");
    sprintf(buffer, "%d", idEnchere);
    strcat(requete, buffer);
    strcat(requete, " ");
    sprintf(buffer, "%d", montantEnchere);
    strcat(requete, buffer);
    strcat(requete, "\n");

    if(Emission(requete)!=1) {
        printf("Erreur d'emission\n");
    }
    message = Reception();
    fflush(stdout);

    retour = atoi(message);



    if(retour == 0){
        printf("Enchère effectuée.\n");
    }
    else{
        messageRetour(retour);
    }

}

void menuAjouterEnchere(){
    char nomProduit[50];
    char url[200];
    char description[200];
    char categorie[50];
    int montant;
    int quantite;
    char lieu[200];
    char requete[700];
    char buffer[100];
    char * message;
    int retour;


    do{
        printf("Veuillez saisir le nom du produit : ");
        fgets(nomProduit, sizeof(nomProduit), stdin);
        clean(nomProduit);
        enleverEspace(nomProduit);
    }while(isVide(nomProduit));

    do{
        printf("Veuillez saisir la description du produit : ");
        fgets(description, sizeof(description), stdin);
        clean(description);
        enleverEspace(description);
    }while(isVide(description));

        do{
        printf("Veuillez saisir une URL pour le produit : ");
        fgets(url, sizeof(url), stdin);
        clean(url);
        enleverEspace(url);
    }while(isVide(url));

    do{
        printf("Veuillez saisir un montant initial pour le produit : ");
        scanf("%d", &montant);
        purger();
    }while(montant < 0 || montant > 2000000);

    do{
        printf("Veuillez saisir une categorie pour le produit : ");
        fgets(categorie, sizeof(categorie), stdin);
        clean(categorie);
        enleverEspace(categorie);
    }while(isVide(categorie));

    do{
        printf("Veuillez saisir l quantité de produit : ");
        scanf("%d", &quantite);
        purger();
    }while(quantite < 1 || quantite > 100);

    do{
        printf("Veuillez saisir le lieu de récupération du produit : ");
        fgets(lieu, sizeof(lieu), stdin);
        clean(lieu);
        enleverEspace(lieu);
    }while(isVide(lieu));

    strcpy(requete, "2 ");
    strcat(requete, nomProduit);
    strcat(requete, " ");

    strcat(requete, description);
    strcat(requete, " ");

    strcat(requete, url);
    strcat(requete, " ");

    sprintf(buffer, "%d", montant);
    strcat(requete, buffer);
    strcat(requete, " ");

    sprintf(buffer, "%d", quantite);
    strcat(requete, buffer);
    strcat(requete, " ");

    strcat(requete, lieu);
    strcat(requete, " ");

    strcat(requete, categorie);
    strcat(requete, "\n");

    if(Emission(requete)!=1) {
        printf("Erreur d'emission\n");
    }
    message = Reception();
    fflush(stdout);

    retour = atoi(message);

    messageRetour(retour);

}

void finirEnchere(){
    char requete[200];
    int retour;
    int idEnchere;
    char *message;
    char buffer[100];

    do{
        printf("Veuillez saisir l'enchère que vous voulez finir : ");
        scanf("%d", &idEnchere);
        purger();
    }while(idEnchere < 0 || idEnchere > 1000);


    strcpy(requete, "4 ");
    sprintf(buffer, "%d", idEnchere);
    strcat(requete, buffer);
    strcat(requete, "\n");

    if(Emission(requete)!=1) {
        printf("Erreur d'emission\n");
    }
    message = Reception();
    fflush(stdout);

    retour = atoi(message);

    messageRetour(retour);

}

void messageRetour(int retour){

    switch(retour){
        case 1:
            printf("Mot de passe invalide.\n");
            break;

        case 2:
            printf("Identifiant invalide.\n");
            break;

        case 3:
            printf("Numéro d'enchère invalide.\n");
            break;

        case 4:
            printf("Montant de l'enchère invalide.\n");
            break;

        case 5:
            printf("Identifiant déjà existant.\n");
            break;

        case 6:
            printf("Ce n'est pas une de vos enchères\n");
            break;

    }

}

