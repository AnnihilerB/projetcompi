#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include "util.h"
struct envg{
    BILENV variablesGlobales;
    NOE corpsGlobale;
    BILFON listeDesFonctionsOuProcedure;
};
typedef struct envg EnvGlobal;


EnvGlobal* creer_environnementGlobal(); 
#endif