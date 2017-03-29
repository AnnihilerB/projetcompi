#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include "environ.h"
#include "util.h"
typedef struct environnementGlobal{
    BILENV variablesGlobales;
    BILFON listeDesFonctions;
} EnvGlobal;


EnvGlobal* creer_environnementGlobal(); 
#endif