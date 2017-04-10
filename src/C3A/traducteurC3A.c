#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traducteurC3A.h"
#include "bilquad.h"
#include "ppascal.tab.h"

int cptNomC3A;
int LireTableau;
int estDansFonction;
EnvGlobal envG;
ListeVarLocAChanger listeVarLoc;
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
BILQUAD traduire_ppascal_vers_C3A(EnvGlobal programme)
{
    envG = programme;
    char* ET = Idalloc();
    ET = "ET";
    cptNomC3A = 0;
    BILQUAD corps = traduire_corps(programme.corpsGlobale, ET);
    BILQUAD fct = traduire_toutes_les_fonctions(programme.listeDesFonctionsOuProcedure);
    cptNomC3A += 1;
    BILQUAD fin = creer_bilquad(creer_quad(etiquette(ET, cptNomC3A), ST, NULL,NULL,NULL));
    
    return concatq(concatq(corps, fin), fct);
}
BILQUAD traduire_appel_fonction (NOE noeud, BILFON listeFonctions, char* etiq)
{    
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
        VAR_LOC var = rech_VAR_LOC(paramActuel->ID);
        BILQUAD instructionParam;
        if (var == NULL)
        {
             instructionParam = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), PARAM, paramActuel->ID, calculArg.fin->RES, NULL));
        }
        else
            instructionParam = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), PARAM, var->nouveau_nom, calculArg.fin->RES, NULL));
        
        b = concatq(b, concatq(calculArg,instructionParam));
        argsEnvoyee = argsEnvoyee->FG;
        paramActuel = paramActuel->SUIV;
        nbArgs ++;
    }
    int tmp = cptNomC3A;
    cptNomC3A += 1;
    b = concatq(b, creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), CALL, etiquette(fonctionTrouvee->ID, -1), intToChar(nbArgs), NULL)));
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
        BILQUAD fg = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AFIND, noeud->FG->ETIQ, fd.fin->RES, VA(cptNomC3A+1)));
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
        BILQUAD b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AFIND, filsG.fin->RES, filsD.fin->RES, VA(cptNomC3A+1)));
        cptNomC3A += 1;
        return concatq(concatq(filsG,filsD), b);
    }
}
BILQUAD recursif_lecture_tableau(NOE noeud, char* etiq)
{
    if (noeud->FG->FG == NULL)
    {
        cptNomC3A += 1;
        BILQUAD fd = traduire_corps(noeud->FD, etiq);
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        BILQUAD fg = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), IND, noeud->FG->ETIQ, fd.fin->RES, VA(cptNomC3A+1)));
        cptNomC3A += 1;
        return concatq(fd, fg);
    }
    else
    {
        BILQUAD filsG = recursif_lecture_tableau(noeud->FG, etiq);
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        BILQUAD filsD = traduire_corps(noeud->FD,etiq);
        cptNomC3A += 1;
        BILQUAD b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), IND, filsG.fin->RES, filsD.fin->RES, VA(cptNomC3A+1)));
        cptNomC3A += 1;
        return concatq(concatq(filsG,filsD), b);
    }
}
BILQUAD traduire_ecriture_tableau (NOE noeud, char* etiq)
{
    BILQUAD b = recursif_ecriture_tableau(noeud, etiq);
}
BILQUAD traduire_lecture_tableau (NOE noeud, char* etiq)
{
    BILQUAD b = recursif_lecture_tableau(noeud, etiq);
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
            cptNomC3A += 1;
            if (estDansFonction == 1)
            {
                VAR_LOC var = rech_VAR_LOC(corps->ETIQ);
                if (var != NULL)
                    b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL, var->nouveau_nom));
                else
                    b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL, corps->ETIQ));
            }
            else
                b = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL, corps->ETIQ));
            
        }
        else 
        {
            //tableau
            if (LireTableau == 1)
            {
                //IND
                b = traduire_lecture_tableau(corps, etiq);
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
        if (corps->FG->codop == V && corps->FG->FG != NULL && corps->FG->FD != NULL)   //AfInd
        {
            int tmp = cptNomC3A;
            cptNomC3A += 1;
            BILQUAD filsD = traduire_corps(corps->FD, etiq);
            cptNomC3A += 1;
            BILQUAD af = traduire_ecriture_tableau(corps->FG, etiq);
            strcpy(af.fin->RES, filsD.fin->RES);
            b = concatq(filsD, af);
        }
        else
        {
            LireTableau = 1;
            int tmp = cptNomC3A;
            cptNomC3A += 1;
            LireTableau = 1;
            BILQUAD filsD = traduire_corps(corps->FD, etiq);
            
            LireTableau = 0;
            cptNomC3A += 1;
            BILQUAD filsG = traduire_corps(corps->FG, etiq);
            cptNomC3A += 1;
            BILQUAD af = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AF, filsG.fin->RES, filsD.fin->RES, NULL));
            if (corps->FD->codop == NewAr)
            {
                cptNomC3A += 1;
                BILQUAD bb = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), AFIND, filsG.fin->RES, filsG.fin->RES, filsD.fin->RES));
                filsD = concatq(filsD, bb);
            }
            b = concatq(concatq(filsD,filsG), af);
            LireTableau = 0;
        }
        
    }
    else if (corps->codop == NewAr)
    {
        int tmp = cptNomC3A;
        cptNomC3A += 1;
        b = traduire_corps(corps->FD, etiq);
        
    }
    else if (corps->codop != Not && corps->codop >= Pl && corps->codop <= Eq)  //Pl,Mo,Mu,And,Or,Lt,Eq
    {
        LireTableau = 1;
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
        int tmp = cptNomC3A; 
        cptNomC3A += 1;
        BILQUAD fg = traduire_corps(corps->FG, etiq);
        cptNomC3A += 1;
        BILQUAD fd = traduire_corps(corps->FD, etiq);
        BILQUAD fils = concatq(fg, fd);
        cptNomC3A += 1;
        BILQUAD pere = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), op, fg.fin->RES, fd.fin->RES, VA(cptNomC3A+1)));
        cptNomC3A += 1;
        b = concatq(fils, pere);
        LireTableau = 0;
    }
    else if (corps->codop == Not)
    {
        int tmp = cptNomC3A;
        
        cptNomC3A += 1;
        BILQUAD fils = traduire_corps(corps->FD, etiq);
        cptNomC3A += 1;
        BILQUAD neg = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), NOT, fils.fin->RES, NULL, VA(cptNomC3A+1));
        cptNomC3A += 1;
        b = concatq(fils, neg);
    }
    else if (corps->codop == Sk)
    {      
        cptNomC3A += 1;
        BILQUAD pere = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL,NULL));        
        b = pere;
    }
    else if (corps->codop == Wh)
    {
        cptNomC3A += 1;
        BILQUAD condition = traduire_corps(corps->FG, etiq);
        cptNomC3A += 1;
        BILQUAD filsBoucle = traduire_corps(corps->FD, etiq);
        cptNomC3A += 1;
        BILQUAD jmpFin = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), JP, NULL,NULL,condition.debut->ETIQ));
        cptNomC3A += 1;
        BILQUAD skipFin = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), SK, NULL,NULL,NULL));
        cptNomC3A += 1;
        BILQUAD boucle = creer_bilquad(creer_quad(etiquette(etiq, cptNomC3A), JZ, condition.fin->RES, NULL, skipFin.debut->ETIQ));
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
        BILQUAD quadElse = creer_bilquad(creer_quad(etiquette(etiq,cptNomC3A), JP, NULL,NULL,finIf.debut->ETIQ));
        
        b = concatq(concatq(concatq(concatq(concatq(condition,quadIf),fd),quadElse),fg),finIf);        
    }
    return b;
    
}

BILQUAD traduire_fonction(LFON fonction)
{
    estDansFonction = 1;
    cptNomC3A = 0;
    BILQUAD b =  traduire_corps(fonction->CORPS, fonction->ID);
    cptNomC3A += 1;
    BILQUAD ret = creer_bilquad(creer_quad(etiquette(fonction->ID, cptNomC3A), RET, NULL,NULL,NULL));
    estDansFonction = 0;
    return concatq(creer_bilquad(creer_quad(etiquette(fonction->ID, -1), SK,NULL,NULL,NULL)),concatq(b,ret));
}
BILQUAD traduire_toutes_les_fonctions(BILFON fonctions)
{
    BILQUAD bil = bilquad_vide();
    LFON f = fonctions.debut;
    while (f != NULL)
    {
        cptNomC3A = 0;
        listeVarLoc = listeVarLocAChanger_vide();
        remplir_listeVarLoc(envG.variablesGlobales, f);
        bil = concatq(bil,traduire_fonction(f));
        f = f->SUIV;
    }
    return bil;
}
void remplir_listeVarLoc(BILENV varGlobale, LFON fonction)
{
    ENV varG = varGlobale.debut;
    while (varG != NULL)
    {
        if (rechercher_env(varG->ID, fonction->PARAM.debut) != NULL || rechercher_env(varG->ID, fonction->VARLOC.debut) != NULL)
        {
            ajouter_variable_locale_a_changer(varG->ID);
        }
        varG = varG->SUIV;
    }
}
ListeVarLocAChanger listeVarLocAChanger_vide()
{
    ListeVarLocAChanger l;
    l.debut = l.fin = NULL;
    return l;
}
void ajouter_variable_locale_a_changer(char* nom)
{
    VAR_LOC v = VAR_LOC_vide();
    strcpy(v->nom_original, nom);
    strcpy(v->nouveau_nom, v->nom_original);
    v->nouveau_nom[strlen(v->nouveau_nom)] = 'L';
    v->nouveau_nom[strlen(v->nouveau_nom)] = '\0';
    if (listeVarLoc.debut == NULL)
    {
        listeVarLoc.debut = listeVarLoc.fin = v;
    }
    else
    {
        listeVarLoc.fin->SUIV = v;
        listeVarLoc.fin = v;
    }
}
VAR_LOC rech_VAR_LOC(char* nom)
{
    VAR_LOC v = listeVarLoc.debut;
    while (v != NULL)
    {
        if (strcmp(nom, v->nom_original) == 0)
            break;
        v = v->SUIV;
    }
    return v;
}
VAR_LOC VAR_LOC_vide()
{
    VAR_LOC v = malloc(sizeof(struct varLocAChanger));
    v->nom_original = Idalloc();
    v->nouveau_nom = Idalloc();
    v->SUIV = NULL;
}

char* etiquette(char* n, int c){
    char *nom = Idalloc();
    if (c >= 0)
        sprintf(nom, "%s%d",n, c);
    else 
        sprintf(nom, "%s",n);
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

