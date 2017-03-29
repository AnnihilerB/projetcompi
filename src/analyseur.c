#include <stdlib.h>
#include "analyseur.h"

EnvGlobal* creer_environnementGlobal()
{
    EnvGlobal* g = malloc(sizeof(EnvGlobal));
    g->corpsGlobale = NULL;
}
