#include <stdlib.h>
#include <string.h>
#include "analyseur.h"
#include "ppascal.tab.h"

void ecrire_type(Type t)
{
    printf("dimension: %d et type: ", t.dim);
    if (t.type == T_ar)
        printf("T_ar ");
    else if (t.type == T_boo)
        printf("T_boo ");
    else if (t.type == T_int)
        printf("T_int ");
    else 
        printf("erreur ");
    printf("\n");
}
EnvGlobal creer_environnementGlobal()
{
    EnvGlobal g;
    g.corpsGlobale = NULL;
    g.variablesGlobales = bilenv_vide();
    g.listeDesFonctionsOuProcedure = bilfon_vide();
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
    if (n->codop == NewAr)
    {
        dimension = -1;
    }
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
    ENV w = copier_env(env);
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
            Type t = renvoie_type_avec_un_noeudVariable(noeud);
            envTrouve->type.dim -= t.dim;
            
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
    else if (noeud->codop == NewAr)
    {
        envTrouve = Envalloc();
        envTrouve->type = renvoie_type_avec_un_noeudVariable(noeud);
    }
    else
    {
        envTrouve = Envalloc();
        envTrouve->type.dim = 0;
        if (noeud->codop == T_boo || noeud->codop == Not || noeud->codop == And || noeud->codop == Or || noeud->codop == Eq || noeud->codop == Lt)
            envTrouve->type.type = T_boo;
        else
            envTrouve->type.type = T_int;
    }
    return envTrouve;
}
