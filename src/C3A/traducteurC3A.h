#ifndef TRADUCTEURC3A_H
#define TRADUCTEURC3A_H
#include "analyseur.h"
#include "environ.h"
enum {PL = 300, MO, MU, AND, OR, NOT, AF, AFC, AFIND, SK, JP, JZ, ST, PARAM, CALL, RET};
char* getStringInstruction(int c);
void traduire_ppascal_vers_C3A(EnvGlobal programme);
void ecrire_parametre_fonction(BILENV param_envoye, BILENV param_fonction, int numEtiquette);  //les param_envoyé sont toujours déjà des valeurs, et les param_fonction sont bons (on y a enlevé, le premier si c'est une fonction)

#endif