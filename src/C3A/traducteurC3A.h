#ifndef TRADUCTEURC3A_H
#define TRADUCTEURC3A_H
#include "analyseur.h"
#include "environ.h"
enum {PL = 300, MO, MU, AND, OR, NOT, AF, AFC, AFIND, SK, JP, JZ, ST, PARAM, CALL, RET};
char* getStringInstruction(int c);
void traduire_ppascal_vers_C3A(EnvGlobal programme);
int traduire_fonction (BILENV param_envoye, LFON f, int numEtiquette);

#endif