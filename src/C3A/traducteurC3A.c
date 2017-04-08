#include <stdio.h>
#include <stdlib.h>
#include "traducteurC3A.h"
#include "bilquad.h"
#include "ppascal.tab.h"

int cptNomC3A;
int estAGaucheAffectation;
EnvGlobal envG;
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
        return -v;
    }
    else
        v = atoi(n);
    return v;
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
    envG = programme;
    char* ET = Idalloc();
    ET = "ET";
    cptNomC3A = 0;
    ecrire_bilquad(traduire_corps(programme.corpsGlobale, ET));
    //ecrire_bilquad(traduire_toutes_les_fonctions(programme->listeDesFonctionsOuProcedure));
    
}
BILQUAD traduire_appel_fonction (NOE noeud, BILFON listeFonctions, char* etiq)
{    
    cptNomC3A += 1;
    LFON fonctionTrouvee = rechercher_lfon(noeud->ETIQ, listeFonctions.debut);
    ENV paramActuel = fonctionTrouvee->PARAM.debut;
    if (paramActuel->ID == NULL)   //alors on utilise pas le premier argument, car c'est le type de retour
        paramActuel = paramActuel->SUIV;
        
    NOE argsEnvoyee = noeud->FG;
    BILQUAD b = bilquad_vide();
    int nbArgs = 0;
    while (paramActuel != NULL)
    {
        cptNomC3A += 1;
        BILQUAD calculArg = traduire_corps(argsEnvoyee->FD, etiq); 
        cptNomC3A += 1;
        BILQUAD instructionParam = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), PARAM, paramActuel->ID, calculArg.fin->RES, NULL));
        b = concatq(b, concatq(calculArg,instructionParam));
        argsEnvoyee = argsEnvoyee->FG;
        paramActuel = paramActuel->SUIV;
        nbArgs ++;
        cptNomC3A += 1;
    }
    int tmp = cptNomC3A;
    cptNomC3A += 1;
    b = concatq(b, creer_bilquad(creer_quad(etiquette(etiq, tmp), CALL, etiquette(fonctionTrouvee->ID, 0), intToChar(nbArgs), NULL)));
    return b;
    
}
BILQUAD recursif_ecriture_tableau (NOE noeud, char* etiq)
{
    if (noeud->FG->FG == NULL)
    {
        cptNomC3A += 1;
        BILQUAD fd = traduire_corps(noeud->FD, etiq);
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        BILQUAD fg = creer_bilquad(creer_quad(etiquette(etiq, tmp), AFIND, noeud->FG->ETIQ, fd.fin->RES, VA(cptNomC3A)));
        cptNomC3A += 1;
        return concatq(fd, fg);
    }
    else
    {
        BILQUAD filsG = recursif_ecriture_tableau(noeud->FG, etiq);
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        BILQUAD filsD = traduire_corps(noeud->FD,etiq);
        cptNomC3A += 1;
        BILQUAD b = creer_bilquad(creer_quad(etiquette(etiq, tmp), AFIND, filsG.fin->RES, filsD.fin->RES, VA(cptNomC3A)));
        return concatq(concatq(filsG,filsD), b);
    }
}
BILQUAD traduire_ecriture_tableau (NOE noeud, char* etiq)
{
    BILQUAD b = recursif_ecriture_tableau(noeud, etiq);
}
BILQUAD traduire_corps(NOE corps, char* etiq)
{
    BILQUAD b = bilquad_vide();
    if (corps->codop == T_boo)
    {
        int val = 1;
        if (strcmp(corps->ETIQ, "false") == 0)
            val = 0;
        //ecrire les bilquad pour une valeur
        b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AFC, intToChar(val), NULL, CT(cptNomC3A+1)));
        cptNomC3A += 2;
    }
    else if (corps->codop == I)
    {
        b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AFC, corps->ETIQ, NULL, CT(cptNomC3A +1)));
            cptNomC3A += 2;
    }
    else if (corps->codop == V)
    {
        if (corps->FG == NULL && corps->FD == NULL)
        {            
            //ecrire bilquad variable
            b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL, corps->ETIQ));
            cptNomC3A += 1;
        }
        else 
        {
            //tableau
            if (estAGaucheAffectation == 1)
            {
                //AFIND
                b = traduire_ecriture_tableau(corps, etiq);
            }
            else
            {
                //IND
            }
        }
        
    }
    else if (corps->codop == Se)
    {
        b = concatq(traduire_corps(corps->FG, etiq), traduire_corps(corps->FD, etiq));
    }
    else if (corps->codop == NPro || corps->codop == NFon)
    {
        b = traduire_appel_fonction(corps, envG.listeDesFonctionsOuProcedure, etiq);
    }
    else if (corps->codop == Af)
    {
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        estAGaucheAffectation = 0;
        BILQUAD filsD = traduire_corps(corps->FD, etiq);
        estAGaucheAffectation = 1;
        cptNomC3A += 1;
        BILQUAD filsG = traduire_corps(corps->FG, etiq);
        cptNomC3A += 1;
        BILQUAD af = creer_bilquad(creer_quad(etiquette(etiq, tmp), AF, filsG.fin->RES, filsD.fin->RES, NULL));
        b = concatq(concatq(filsD,filsG), af);
        
    }
    else if (corps->codop != Not && corps->codop >= Pl && corps->codop <= Eq)  //Pl,Mo,Mu,And,Or,Lt,Eq
    {
        int op;
        switch(corps->codop)
        {
            case Pl: op = PL; break;
            case Mo: op = MO; break;
            case Mu: op = MU; break;
            case And: op = AND; break;
            case Or: op = OR; break;
            case Lt: op = LT; break;
            case Eq: op = EQ; break;
        }
        int tmp = cptNomC3A; //1
        cptNomC3A += 1;
        BILQUAD fg = traduire_corps(corps->FG, etiq);
        cptNomC3A += 1;
        BILQUAD fd = traduire_corps(corps->FD, etiq);
        BILQUAD fils = concatq(fg, fd);
        cptNomC3A += 1;
        BILQUAD pere = creer_bilquad(creer_quad(etiquette(etiq, tmp), op, fg.fin->RES, fd.fin->RES, VA(cptNomC3A)));
        
        b = concatq(fils, pere);
    }
    else if (corps->codop == Not)
    {
        int tmp = cptNomC3A;
        
        cptNomC3A += 1;
        BILQUAD fils = traduire_corps(corps->FD, etiq);
        cptNomC3A += 1;
        BILQUAD neg = creer_bilquad(creer_quad(etiquette(etiq, tmp), NOT, corps->ETIQ, NULL, fils.fin->RES));
        b = concatq(fils, neg);
    }
    else if (corps->codop == Sk)
    {        
        BILQUAD pere = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL,NULL));
        cptNomC3A += 1;
        b = pere;
    }
    else if (corps->codop == Wh)
    {
        BILQUAD condition = traduire_corps(corps->FG, etiq);
        BILQUAD filsBoucle = traduire_corps(corps->FD, etiq);
        BILQUAD jmpFin = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), JP, NULL,NULL,condition.debut->ETIQ));
        BILQUAD skipFin = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A + 2), SK, NULL,NULL,NULL));
        BILQUAD boucle = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A + 1), JZ, condition.fin->RES, NULL, skipFin.debut->ETIQ));
        cptNomC3A += 3;
        b = concatq(concatq(concatq(concatq(condition, boucle), filsBoucle),jmpFin),skipFin);
    }
    else if (corps->codop == If)
    {
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        BILQUAD condition = traduire_corps(corps->FG, etiq);
        cptNomC3A += 1;
        BILQUAD fd = traduire_corps(corps->FD->FG, etiq);
        cptNomC3A += 1;
        BILQUAD fg = traduire_corps(corps->FD->FD, etiq);
        cptNomC3A += 1;
        BILQUAD finIf = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL,NULL));
        cptNomC3A += 1;
        BILQUAD quadIf = creer_bilquad(creer_quad(etiquette(etiq,cptNomC3A), JZ, condition.fin->RES, NULL, fg.debut->ETIQ));
        cptNomC3A += 1;
        BILQUAD quadElse = creer_bilquad(creer_quad(etiquette(etiq,cptNomC3A+2), JP, NULL,NULL,finIf.debut->ETIQ));
        b = concatq(concatq(concatq(concatq(concatq(condition,quadIf),fd),quadElse),fg),finIf);        
    }
    return b;
    
}
BILQUAD traduire_fonction(LFON fonction)
{
    cptNomC3A = 0;
    return traduire_corps(fonction->CORPS, fonction->ID);
}
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions)
{
    BILQUAD bil = bilquad_vide();
    LFON f = fonctions.debut;
    while (f != NULL)
    {
        bil = concatq(bil,traduire_fonction(f));
        f = f->SUIV;
    }
    return bil;
}

char* etiquette(char* n, int c){
    char *nom = Idalloc();
    sprintf(nom, "%s%d",n, c);
    return nom;
}
char* CT(int c){
    char *nom = malloc(7);
    sprintf(nom, "CT%d", c);
    return nom;
}
char* VA(int c){
    char *nom = malloc(7);
    sprintf(nom, "VA%d", c);
    return nom;
}

