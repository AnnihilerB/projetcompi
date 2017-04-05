#include <stdlib.h>
#include <string.h>
#include "analyseur.h"
#include "ppascal.tab.h"

EnvGlobal creer_environnementGlobal()
{
    EnvGlobal g = malloc(sizeof(EnvGlobal));
    g->corpsGlobale = NULL;
    return g;
}

Type renvoie_type_fonction (LFON fonctionOuProcedure)
{
    Type t;
    t.type = t.dim = 0;
    if (fonctionOuProcedure->PARAM.debut->ID == NULL)
        t = fonctionOuProcedure->PARAM.debut->type;
    return t;
}
Type renvoie_type_avec_un_noeudVariable(NOE n)
{
    int dimension = 0;
    NOE w = n;
    while (w->FG != NULL)
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
int compare_type(Type t1, Type t2)
{
    if (t1.type == t2.type && t1.dim == t2.dim)
        return 1;
    return 0;
}

ENV rechercher_env (char* nom, ENV env)
{
    ENV w = env;
    while (w != NULL)
    {
        if (strcmp(nom, w->ID) == 0)
            return w;
        w = w->SUIV;
    }
    return NULL;
}
LFON rechercher_lfon(char* nom, LFON lfon)
{
    if (nom == NULL)
        return NULL;
    LFON w = lfon;
    while (w != NULL)
    {
        if (strcmp(nom, w->ID) == 0)
            return w;
        w = w->SUIV;
    }
    return NULL;
}
int trouver_dimension_type_noeud(NOE noeud)
{
    int dimension = 0;
    NOE w = noeud->FG;
    while (w != NULL)
    {
        dimension ++;
        w = w->FG;
    }
    return dimension;
}
ENV existe (NOE noeud, BILFON listeFonctions, BILENV listeVariablesGlobale, BILENV listeVariablesLocales)
{
    if (noeud == NULL)
        return NULL;
    ENV envTrouve = NULL;
    char* nomENV = NULL;
    if (noeud->codop == V)
    {
        if (noeud->FG != NULL && noeud->FD != NULL) //c'est un tableau
        {
            nomENV = noeud->ETIQ;
            
            envTrouve = rechercher_env(nomENV, listeVariablesLocales.debut);
            if (envTrouve == NULL && (envTrouve = rechercher_env(nomENV, listeVariablesGlobale.debut)) == NULL)
                return NULL;
            if (envTrouve->type.dim != trouver_dimension_type_noeud(noeud))     //si son type la dimension de la variable n'est pas égale à la dimension déclaré, alors on dit que la variable a pour type T_ar et donc il a un mauvais type
                envTrouve->type.type = T_ar;
            envTrouve->type.dim = 0;
            
        }
        else        //variable "classique"
        {
            nomENV = noeud->ETIQ;            
            envTrouve = rechercher_env(nomENV, listeVariablesLocales.debut);
            if (envTrouve == NULL)
                envTrouve = rechercher_env(nomENV, listeVariablesGlobale.debut);
        }
        
        
    }
    else if (noeud->codop == NFon)
    {
        nomENV = noeud->ETIQ;
        LFON lfonTrouvee = NULL;
        lfonTrouvee = rechercher_lfon(nomENV, listeFonctions.debut);        
        if (lfonTrouvee != NULL)
        {
            envTrouve = Envalloc();
            envTrouve->ID = lfonTrouvee->ID;
            envTrouve->type = renvoie_type_fonction(lfonTrouvee);
        }
    }
    else
    {
        envTrouve = Envalloc();
        envTrouve->type.dim = 0;
        if (noeud->codop == T_boo || noeud->codop == Not || noeud->codop == And || noeud->codop == Or || noeud->codop == Eq)
        {
            envTrouve->type.type = T_boo;
            
        printf("codop: %d et etiq: %s\n", noeud->codop, noeud->ETIQ);
        }
        else
            envTrouve->type.type = T_int;
        
    }
    return envTrouve;
}
