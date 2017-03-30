#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include "util.h"
typedef struct envg{
    BILENV variablesGlobales;
    NOE corpsGlobale;
    BILFON listeDesFonctionsOuProcedure;
} *EnvGlobal;



EnvGlobal creer_environnementGlobal(); 
Type renvoie_type_avec_un_noeud(NOE n);
int compare_type(Type type, NOE varATester); //retourne 0 si type != type de varATester sion renvoie 1
#endif
