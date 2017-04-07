#include <stdio.h>
#include <stdlib.h>
#include "traducteurC3A.h"
#include "bilquad.h"
#include "ppascal.tab.h"

char* getStringInstruction(int c)
{
    switch (c)
    {
        case PL:
            return "Pl";
        case MO:
            return "Mo";
        case MU:
            return "Mu";
        case AND:
            return "And";
        case OR:
            return "Or";
        case NOT:
            return "Not";
        case AFIND:
            return "AfInd";
        case PARAM:
            return "Param";
        case CALL:
            return "Call";
        case RET:
            return "Ret";
        case AF:
            return "Af";
        case AFC:
            return "Afc";
        case SK:
            return "Sk";
        case JP:
            return "Jp";
        case JZ:
            return "Jz";
        case ST:
            return "St";
    }
    
}
void traduire_ppascal_vers_C3A(EnvGlobal programme)
{
    ListeFonctionsTraduites liste_fonctionsTraduites = ListeFonctionsTraduites_vide();
    traduire_toutes_les_fonctions(programme.listeDesFonctionsOuProcedure, &liste_fonctionsTraduites);
}
BILQUAD traduire_corps(char* nomFonctionActuel, NOE corps)
{
}
BILQUAD traduire_fonction(ListeFonctionsTraduites* liste, LFON fonction)
{
}
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions, ListeFonctionsTraduites* listeFonctions)
{
    
}
ListeFonctionsTraduites ListeFonctionsTraduites_vide()
{
    ListeFonctionsTraduites l;
    l.debut = l.fin = NULL;
    return l;
}
void ajouter_ListeFonctionsTraduites (ListeFonctionsTraduites* liste, FonTraduite ftrad)
{
    if (ftrad != NULL)
    {
        if (liste->debut == NULL)
            liste->debut = liste->fin = ftrad;
        else
        {
            liste->fin->SUIV = ftrad;
            ftrad->SUIV = NULL;
            liste->fin = ftrad; 
        }
    }
}
void liberer_ListeFonctionstraduites (ListeFonctionsTraduites liste)
{
}
