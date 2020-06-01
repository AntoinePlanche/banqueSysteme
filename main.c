#include <stdio.h>
#include <stdlib.h>
#include "gestionCompte.h"

int main()
{
    Banque BNPParibas = NULL;
    for(int i = 0; i<3 ; i++)
    {
      BNPParibas = addClient(BNPParibas);
    }
    displayClient(BNPParibas);
    operation(2,BNPParibas);
    displayClient(BNPParibas);
    displaySingleClient(rechercheClient("Planche","Antoine",BNPParibas));
    liberez(BNPParibas);
    displayClient(BNPParibas);
    return 0;
}
