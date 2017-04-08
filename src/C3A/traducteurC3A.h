#ifndef TRADUCTEURC3A_H
#define TRADUCTEURC3A_H
#include "analyseur.h"
#include "environ.h"
#include "bilquad.h"
enum {PL = 300, MO, MU, AND, OR, LT, EQ,IND, NOT, AF, AFC, AFIND, SK, JP, JZ, ST, PARAM, CALL, RET};


char* getStringInstruction(int c);
char* intToChar(int c);
char* etiquette(char* n, int c);
char* CT(int c);
char* VA(int c);
int charToInt (char* n);
char* intToChar(int c);
void traduire_ppascal_vers_C3A(EnvGlobal programme);
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions);
BILQUAD traduire_fonction(LFON fonction);
BILQUAD traduire_corps(NOE corps, char* etiq);
BILQUAD traduire_appel_fonction (NOE noeud, BILFON listeFonctions, char* etiq);

#endif
