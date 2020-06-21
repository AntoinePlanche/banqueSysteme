#include <stdio.h>
#include <stdlib.h>
#include "gestionCompte.h"

int main()
{
    Banque BNPParibas = NULL;
    for(int i = 0; i<1 ; i++)
    {
      BNPParibas = addClient(BNPParibas);
      system("cls");
    }
    displayClient(BNPParibas);
    editerCompte(BNPParibas);
    OperationCompte("Planche","Antoine",BNPParibas);
    liberez(BNPParibas);
    return 0;
}
