#include <stdio.h>
#include <stdlib.h>
#include "traducteurC3A.h"
#include "ppascal.tab.h"

char* getStringInstruction(int c)
{
    switch (c)
    {
        case PL:
            return "Pl";
        case MO:
            return "Mo";
        case MU:
            return "Mu";
        case AND:
            return "And";
        case OR:
            return "Or";
        case NOT:
            return "Not";
        case AFIND:
            return "AfInd";
        case PARAM:
            return "Param";
        case CALL:
            return "Call";
        case RET:
            return "Ret";
        case AF:
            return "Af";
        case AFC:
            return "Afc";
        case SK:
            return "Sk";
        case JP:
            return "Jp";
        case JZ:
            return "Jz";
        case ST:
            return "St";
    }
    
}
void traduire_ppascal_vers_C3A(EnvGlobal programme)
{
    
}
void ecrire_parametre_fonction(BILENV param_envoye, BILENV param_fonction, int numEtiquette)  //les param_envoyé sont toujours déjà des valeurs, et les param_fonction sont bons (on y a enlevé, le premier si c'est une fonction)
{
    
}