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
void traduire_ppascal_vers_C3A(EnvGlobal programme);
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions, ListeFonctionsTraduites* listeFonctions);
BILQUAD traduire_fonction(ListeFonctionsTraduites* liste, LFON fonction);
BILQUAD traduire_corps(char* nomFonctionActuel, NOE corps);//nomFonctionActuel: donne le nom de la fonction, d'où vient le corps, si NULL alors c'est que le corps est hors d'une fonction


#endif
