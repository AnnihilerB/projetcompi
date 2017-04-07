#include <stdio.h>
#include <stdlib.h>
#include "traducteurC3A.h"
#include "bilquad.h"
#include "ppascal.tab.h"

char* intToChar(int c){
    char* nom = malloc(7);
    sprintf(nom, "%d", c);
    return nom;
}
int charToInt (char* n)
{
    int v;
    if (n != NULL && n[0] == '-')
    {
        v = atoi(&n[1]);
    }
    else
        v = atoi(n);
}
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
    ecrire_bilquad(traduire_toutes_les_fonctions(programme->listeDesFonctionsOuProcedure, &liste_fonctionsTraduites));
    
}
BILQUAD traduire_corps(NOE corps, char* etiq, int* numEtiquette)
{
    if (corps->codop == T_boo)
    {
        int val = 1;
        if (strcmp(corps->ETIQ, "false") == 0)
            val = 0;
        //ecrire les bilquad pour une valeur
        BILQUAD b = creer_bilquad(creer_quad(etiquette(etiq, numEtiquette), AFC, intToChar(val), NULL, CT(numEtiquette +1)));
        *(numEtiquette) += 2;
    }
    else if (corps->codop == I)
    {
       BILQUAD b = creer_bilquad(creer_quad(etiquette(etiq, numEtiquette), AFC, intToChar(intToChar(corps->ETIQ)), NULL, CT(numEtiquette +1)));
       *(numEtiquette) += 2;
        //ecrire les bilquad pour une valeur
    }
    else if (corps->codop == V)
    {
        if (corps->FG == NULL && corps->FD == NULL)
        {
            //ecrire bilquad variable
        }
        else 
        {
            //tableau
        }
        
    }
    else if (corps->codop == NPro || corps->codop == NFon)
    {
    }
    else if (corps->codop == Af)
    {
    }
    else if (corps->codop != Not && corps->codop >= Pl && corps->codop <= Eq)  //Pl,Mo,Mu,And,Or,Lt,Eq
    {
        
    }
    else if (corps->codop == Not)
    {
    }
    else if (corps->codop == Sk)
    {
    }
    else if (corps->codop == Wh)
    {
    }
    else if (corps->codop == If)
    {
    }
    
}
BILQUAD traduire_fonction(ListeFonctionsTraduites* liste, LFON fonction)
{
    int numEtiquette = 0;
    return traduire_corps(fonction->CORPS, fonction->ID, &numEtiquette);
}
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions, ListeFonctionsTraduites* listeFonctions)
{
    BILQUAD bil = bilquad_vide();
    LFON f = fonctions.debut;
    while (f != NULL)
    {
        bil = concatq(bil,traduire_fonction(listeFonctions, f));
        f = f->SUIV;
    }
    return bil;
}
ListeFonctionsTraduites ListeFonctionsTraduites_vide()
{
    ListeFonctionsTraduites l;
    l.debut = l.fin = NULL;
    return l;
}
char* etiquette(char* n, int c){
    char *nom = malloc(7);
    sprintf(nom, "%s%d",n, c);
    return nom;
}
char* CT(int c){
    char *nom = malloc(7);
    sprintf(nom, "CT%d", c);
    return nom;
}
char* Va(int c){
    char *nom = malloc(7);
    sprintf(nom, "VA%d", c);
    return nom;
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
