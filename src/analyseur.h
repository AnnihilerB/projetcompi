#ifndef ANALYSEUR_H
#define ANALYSEUR_H
#include "util.h"
typedef struct envg{
    BILENV variablesGlobales;
    NOE corpsGlobale;
    BILFON listeDesFonctionsOuProcedure;
} *EnvGlobal;



EnvGlobal creer_environnementGlobal(); 
int compare_type(Type type, NOE varATester); //l'idée c'est que le type de varATester est en fait son filsGauche et que son filsGauche peut avoir un filsGauche ETC donc on va parcourir ça et voir si c'est égale à type (en additionnant la valeur des filsGauche)
#endif
