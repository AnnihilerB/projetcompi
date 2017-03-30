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
Type renvoie_type_avec_un_noeud(NOE n)
{
    int dimension = 0;
    NOE w = n->FG;
    while (w != NULL)
    {
        dimension ++;
        w = w->FG;
    }
    Type t;
    t.dim = dimension;
    if (w != NULL)
        t.type = w->codop;
    else
        t.type = n->codop;
    return t;
}
int compare_type(Type type, NOE varATester)
{
    Type t = renvoie_type_avec_un_noeud(varATester);
    if (t.type == type.type && t.dim == type.dim)
        return 1;
    else
        return 0;
}
