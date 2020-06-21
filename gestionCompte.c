#include <stdio.h>
#include <stdlib.h>
#include "gestionCompte.h"
#include <string.h>


Banque initializeBanque(Banque banque)
{
    if(banque == NULL)
    {
        banque = (Banque)malloc(sizeof(Client));
        if(banque == NULL)
        {
            printf("erreur d'allocation");
            exit(1);
        }
        banque->next = NULL;
        return banque;
    }
    else
    {
        Banque temp = banque;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (Banque)malloc(sizeof(Client));
        if(temp->next == NULL)
        {
            printf("erreur d'allocation");
            exit(1);
        }
        temp->next->next = NULL;
        return banque;
    }

}

void liberez(Banque banque)
{
    int reponse;
    do{
       printf("Voulez-vous supprimer un client ou la banque en entier\n1->Banque\n2->Client\n");
       scanf("%i",&reponse);
    }while(reponse != 1 && reponse != 2);
    if(reponse == 1)
    {
        Banque temp = NULL;
        while(banque != NULL)
        {
            temp = banque;
            banque = banque->next;
            free(temp);
        }

    }
    else
    {
        Banque temp = banque;
        int numeroClient;
        printf("quel client voulez-vous supprimez ?\n");
        scanf("%i",&numeroClient);
        while(temp->next->compte.numeroDeCompte != numeroClient && temp != NULL)
        {
            temp = temp->next;
        }
        if(temp->next->next !=NULL)
        {
            temp->next = temp->next->next;
            free(temp->next);
        }
        else
        {
            free(temp->next);
            temp->next = NULL;
        }
    }
}

Banque addClient(Banque banque)
{
    banque = initializeBanque(banque);
    Banque temp = banque;
    int numeroDuCompte = 1;
    while(temp->next != NULL)
    {
        temp = temp->next;
        numeroDuCompte++;
    }
    int typeClient;
    printf("Tapez votre nom.\n");
    scanf("%s",temp->nom);
    printf("Tapez votre prenom.\n");
    scanf("%s",temp->prenom);
    printf("Tapez votre adresse.\n");
    scanf("%s",temp->adresse);
    printf("Tapez le solde initiale de votre compte.\n");
    scanf("%i",&temp->compte.solde);
    temp->compte.numeroDeCompte = numeroDuCompte;
    do{
        printf("etes vous un client court ou resilie.\n1->court\n2->resilie\n");
        scanf("%i",&typeClient);
    }while(typeClient != 1 && typeClient != 2);
    if(typeClient == 1)
    {
        temp->typeClient = court;
    }
    else
    {
        temp->typeClient = resilie;
    }

    for(int i=0; i < 20; i++)
    {
        temp->compte.derniereOperation[i].typeOperation = noneType;
        temp->compte.derniereOperation[i].jour = 0;
        temp->compte.derniereOperation[i].mois = 0;
        temp->compte.derniereOperation[i].annee = 0;
        temp->compte.derniereOperation[i].montant = 0;
    }
    return banque;
}

void displayClient(Banque societeGeneral)
{
    Banque temp = societeGeneral;
    while(temp != NULL)
    {
        displaySingleClient(temp);
        temp = temp->next;
    }
}

void displaySingleClient(Client* temp)
{
    if(temp != NULL)
    {
        printf("Client numero : %i, prenom est :%s, nom est : %s, adresse est : %s, solde de : %i",(temp->compte).numeroDeCompte, temp->prenom, temp->nom, temp->adresse, (temp->compte).solde);
        if(temp->typeClient == court)
        {
            printf(", client temporaire.\n");
        }
        else
        {
            printf(", client long terme.\n");
        }
    }
    else
    {
        printf("Client introuvable");
    }

}

void operation(int numeroClient, Banque banque)
{
    Banque temp = banque;
    while(temp != NULL)
    {
        if(temp->compte.numeroDeCompte == numeroClient)
        {
            break;
        }
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("compte inexistant !\n");
    }
    else
    {
        int reponse;
        do{
                printf("Quelle operation voulez vous faire ?\n1->depot\n2->retrait\n");
                scanf("%i",&reponse);
        }while(reponse != 1 && reponse != 2);
        if(reponse == 1)
        {
            Depot(temp);
        }
        else
        {
            Retrait(temp);
        }
    }
}

void Depot(Banque temp)
{
    int depot;
    printf("combien voulez vous deposer ?\n");
    scanf("%i",&depot);
    temp->compte.solde += depot;
    Operation nouvelle;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    nouvelle.jour = local->tm_mday;
    nouvelle.mois = local->tm_mon + 1;
    nouvelle.annee = local->tm_mon + 1900;
    nouvelle.montant = depot;
    nouvelle.typeOperation = depot;
    nouvelle.montant = depot;

    Operation temporaireuno;
    Operation temporairedeuxio;
    temporaireuno = temp->compte.derniereOperation[0];
    temp->compte.derniereOperation[0] = nouvelle;
    for(int i = 1; i<20; i++)
    {
        temporairedeuxio = temp->compte.derniereOperation[i];
        temp->compte.derniereOperation[i] = temporaireuno;
        temporaireuno = temporairedeuxio;
    }
}

void Retrait(Banque temp)
{
    int retrait;
    printf("combien voulez vous retirer ?\n");
    scanf("%i",&retrait);
    temp->compte.solde -= retrait;
    Operation nouvelle;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    nouvelle.jour = local->tm_mday;
    nouvelle.mois = local->tm_mon + 1;
    nouvelle.annee = local->tm_mon + 1900;
    nouvelle.montant = depot;
    nouvelle.typeOperation = retrait;
    nouvelle.montant = retrait;

    Operation temporaireuno;
    Operation temporairedeuxio;
    temporaireuno = temp->compte.derniereOperation[0];
    temp->compte.derniereOperation[0] = nouvelle;
    for(int i = 1; i<20; i++)
    {
        temporairedeuxio = temp->compte.derniereOperation[i];
        temp->compte.derniereOperation[i] = temporaireuno;
        temporaireuno = temporairedeuxio;
    }
}

Banque rechercheClient(char* nom,char* prenom,Banque societeGeneral)
{
    Banque temp = societeGeneral;
    int reponse = 2;
    while(reponse == 2)
    {
        while( temp != NULL &&(strcmp(temp->nom,nom) || strcmp(temp->prenom,prenom)) )
        {
            temp = temp->next;
        }
        if(temp == NULL)
        {
            printf("Client introuvable\n");
            return temp;
        }
        else
        {
            printf("Le client est-il bien: \n");
            displaySingleClient(temp);
            do{
                printf("1->OUI\n2->NON\n");
                scanf("%i",&reponse);
            }while(reponse != 1 && reponse != 2);
            if(reponse == 2)
            {
                temp = temp->next;
            }
        }
    }
    return temp;
}

void editerCompte(Banque bnp)
{
    FILE* enregistrementClient = NULL;
    enregistrementClient = fopen("clients.txt","w+");
    if(enregistrementClient == NULL)
    {
        printf("impossible d'ouvrir le fichier");
    }
    Banque temp = bnp;
    while(temp != NULL)
    {
        fprintf(enregistrementClient,"%i;%s;%s;%s;%i",(temp->compte).numeroDeCompte, temp->prenom, temp->nom, temp->adresse, (temp->compte).solde);
        if(temp->typeClient == court)
        {
            fprintf(enregistrementClient,";t\n");
        }
        else
        {
            fprintf(enregistrementClient,";lg\n");
        }
        temp = temp->next;
    }
    fclose(enregistrementClient);
}

void OperationCompte(char* nom, char* prenom, Banque SG)
{
    int reponse;
    SG = rechercheClient(nom,prenom,SG);
    do{
        printf("Quel operation souhaitez-vous realiser ?\n0->Rien\n1->Afficher le solde du compte\n2->Depot Argent\n3->retrait argent\n4->Edition des dernieres operations sur l'ecran\n5->Edition des dernieres operations sur un fichier\n");
        scanf("%i",&reponse);
    }while(reponse<0 || reponse > 5 );
    switch(reponse)
    {
        case 0 : return;
            break;
        case 1 : printf("%i\n",SG->compte.solde);
            break;
        case 2 : Depot(SG);
            break;
        case 3 : Retrait(SG);
            break;
        case 4 : EditionOperationEcran(SG);
            break;
        default : EditionOperationFichier(SG,nom,prenom);
    }
}

void EditionOperationEcran(Banque SG)
{
    for(int i = 0; i < 20; i++){
        printf("L'operation %i;",i);
        if((int)SG->compte.derniereOperation[i].typeOperation == 0)
        {
            printf(" effectue le %i/%i/%i; d'un montant de %i; etait un retrait\n",SG->compte.derniereOperation[i].jour,SG->compte.derniereOperation[i].mois,SG->compte.derniereOperation[i].annee,SG->compte.derniereOperation[i].montant);
        }
        else if ((int)SG->compte.derniereOperation[i].typeOperation == 1)
        {
            printf(" effectue le %i/%i/%i; d'un montant de %i; etait un depot\n",SG->compte.derniereOperation[i].jour,SG->compte.derniereOperation[i].mois,SG->compte.derniereOperation[i].annee,SG->compte.derniereOperation[i].montant);
        }
        else
        {
            printf(" ****** \n");
        }
    }
}

void EditionOperationFichier(Banque SG, char* nom, char* prenom)
{
    char filename[50];
    strcpy(filename, nom);
    strcat(filename, " ");
    strcat(filename, prenom);
    strcat(filename,".txt");
    FILE* operationClient = NULL;
    operationClient = fopen(filename,"w+");

    for(int i = 0; i < 20; i++){
        fprintf(operationClient,"L'operation %i;",i);
        if((int)SG->compte.derniereOperation[i].typeOperation == 0)
        {
            fprintf(operationClient," effectue le %i/%i/%i; d'un montant de %i; etait un retrait\n",SG->compte.derniereOperation[i].jour,SG->compte.derniereOperation[i].mois,SG->compte.derniereOperation[i].annee,SG->compte.derniereOperation[i].montant);
        }
        else if ((int)SG->compte.derniereOperation[i].typeOperation == 1)
        {
            fprintf(operationClient," effectue le %i/%i/%i; d'un montant de %i; etait un depot\n",SG->compte.derniereOperation[i].jour,SG->compte.derniereOperation[i].mois,SG->compte.derniereOperation[i].annee,SG->compte.derniereOperation[i].montant);
        }
        else
        {
            fprintf(operationClient," ****** \n");
        }
    }
}
