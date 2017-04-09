#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include "util.h"
typedef struct envg{
    BILENV variablesGlobales;
    NOE corpsGlobale;
    BILFON listeDesFonctionsOuProcedure;
} EnvGlobal;



EnvGlobal creer_environnementGlobal(); 
Type renvoie_type_fonction (LFON fonctionOuProcedure);
Type renvoie_type_avec_un_noeudVariable(NOE n);
int compare_type(Type t1, Type t2); //retourne 0 si t1 != t2 1 sinon
ENV rechercher_env (char* nom, ENV env);
LFON rechercher_lfon(char* nom, LFON lfon);
ENV existe (NOE noeud, BILFON listeFonctions, BILENV listeVariablesGlobale, BILENV listeVariablesLocales); //remplie le type de ENV en même temps
void ecrire_type(Type t);
#endif
