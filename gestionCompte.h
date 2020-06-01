#ifndef GESTIONCOMPTE_H_INCLUDED
#define GESTIONCOMPTE_H_INCLUDED
#include <time.h>

typedef enum type{
retrait,
depot,
noneType
}Type;

typedef enum typeclient{
court,
resilie
}Typeclient;

typedef struct operation{
Type typeOperation;
int montant;
int jour;
int mois;
int annee;
}Operation;

typedef struct compte{
int numeroDeCompte;
int solde;
Operation derniereOperation[20];
}Compte;

typedef struct client{
Typeclient typeClient;
char nom[20];
char prenom[20];
char adresse[20];
Compte compte;
struct client* next;
}Client;

typedef Client* Banque;

Banque initializeBanque(Banque banque);
Banque addClient(Banque banque);
void liberez(Banque banque);
void displayClient(Banque societeGeneral);
void displaySingleClient(Client* temp);
void operation(int numeroClient, Banque banque);
Banque rechercheClient(char* nom,char* prenom,Banque societeGeneral);

#endif // GESTIONCOMPTE_H_INCLUDED
