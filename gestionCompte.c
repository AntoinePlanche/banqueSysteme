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
        while(banque == NULL)
        {
            free(banque);
            banque = banque->next;
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
        else
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
