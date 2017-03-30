#include <stdlib.h>
#include "analyseur.h"

EnvGlobal creer_environnementGlobal()
{
    EnvGlobal g = malloc(sizeof(EnvGlobal));
    g->corpsGlobale = NULL;
    return g;
}
int renvoie_type(BILENV* variables, char* nomVar)
{
    ENV varTrouvee = rech2(nomVar, variables->debut, NULL);
    if (varTrouvee == NULL)
        return -1;
    return varTrouvee->VAL;
}
int compare_type(int type, NOE varATester)
{
    int somme = varATester->codop;
    NOE w = varATester->FG;
    while (w != NULL)
    {
        somme += w->codop;
        w = w->FG;
    }
    return somme;
}
