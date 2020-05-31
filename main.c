#include <stdio.h>
#include <stdlib.h>
#include "gestionCompte.h"

int main()
{
    Banque BNPParibas = NULL;
    for(int i = 0; i<5 ; i++)
    {
      BNPParibas = addClient(BNPParibas);
    }
    displayClient(BNPParibas);
    operation(2,BNPParibas);
    operation(2,BNPParibas);
    displayClient(BNPParibas);
    liberez(BNPParibas);
    return 0;
}
