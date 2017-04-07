#ifndef TRADUCTEURC3A_H
#define TRADUCTEURC3A_H
#include "analyseur.h"
#include "environ.h"
#include "bilquad.h"
enum {PL = 300, MO, MU, AND, OR, LT, IND, NOT, AF, AFC, AFIND, SK, JP, JZ, ST, PARAM, CALL, RET};


typedef struct fonctionTraduite {
    char* nom;
    BILQUAD bilquadFonction;
    struct fonctionTraduite* SUIV;
}*FonTraduite;
typedef struct listeFonctionTraduite{
    FonTraduite debut;
    FonTraduite fin;
}ListeFonctionsTraduites;

ListeFonctionsTraduites ListeFonctionsTraduites_vide();
void ajouter_ListeFonctionsTraduites (ListeFonctionsTraduites* liste, FonTraduite ftrad);
void liberer_ListeFonctionstraduites (ListeFonctionsTraduites liste);

char* getStringInstruction(int c);
char* intToChar(int c);
char* etiquette(char* n, int c);
char* CT(int c);
char* Va(int c);
int charToInt (char* n);
void traduire_ppascal_vers_C3A(EnvGlobal programme);
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions, ListeFonctionsTraduites* listeFonctions);
BILQUAD traduire_fonction(ListeFonctionsTraduites* liste, LFON fonction);
BILQUAD traduire_corps(NOE corps, char* etiq, int* numEtiquette);

#endif
