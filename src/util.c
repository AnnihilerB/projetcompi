#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "environ.h"
#include "analyseur.h"
#include "ppascal.tab.h"
#include <stdbool.h>

void ecrire_noe(NOE noe){
  printf("Code OP : %d\n", noe->codop);
  printf("Etiquette : %s\n", noe->ETIQ);
  printf("Fils gauche : \n");
  ecrire_noe(noe->FG);
  printf("Fils droit : \n");
  ecrire_noe(noe->FD);
}

NOE copier_noe(NOE noe){
  NOE noeudCopie = malloc(sizeof(struct noeud));
  noeudCopie->codop = noe->codop;
  noeudCopie->ETIQ = strdup(noe->ETIQ);
  if (noe->FG != NULL)
    noeudCopie->FG = copier_noe(noe->FG);
  if (noe->FD != NULL)
    noeudCopie->FD = copier_noe(noe->FD);
  return noeudCopie;

}

NOE Nalloc()
{
    struct noeud *noe = malloc(sizeof(struct noeud));
    noe->codop = 0;
    noe->ETIQ = noe->FG = noe->FD = NULL;
    return noe;
}

LFON Lfonalloc()
{
    struct cellfon *lfon = malloc(sizeof(struct cellfon));
    lfon->ID = NULL;
    lfon->PARAM = bilenv_vide();
    lfon->VARLOC =  bilenv_vide();
    lfon->CORPS =  NULL;
    lfon->SUIV = NULL;
    return lfon;
}

void prefix(NOE n){

	if(n!=NULL){
		printf("%d, %s\n", n->codop, n->ETIQ);
		prefix(n->FG);
		prefix(n->FD);
	}
}

ENV creer_env(char *etiq, int val){

	ENV e = Envalloc();
	e->ID = etiq;
	e->VAL = val;
    e->SUIV = NULL;
	return e;
}

ENV copier_env(ENV  env){

    ENV e = NULL;

    if(env !=NULL){
        e = creer_env(env->ID, env->VAL);
        e->SUIV= copier_env(env->SUIV);
    }
	
	return e;
}

char *nomop(int codop){

	switch(codop)
    {
    case(T_boo): return("T_boo");
    case(T_int): return("T_int");
    case(Def): return("Def");
    case(Dep): return("Dep");
    case(true): return("true");
    case(false): return("false");
    case(Se): return("Se");
    case(If): return("If");
    case(Th): return("Th");
    case(El): return("El");
    case(Var): return("Var");
    case(Wh): return("Wh");
    case(Do):return("Do");
    case(Af): return("Af");
    case(Sk): return("Sk");
    case(Pl): return("Pl");
    case(Mo): return("Mo");
    case(Mu): return("Mu");
    case(And): return("And");
    case(Or): return("Or");
    case(Not): return("Not");
    case(Lt): return("Lt");
    case(Eq): return("Eq");
    };

}

ENV rech2(char *chaine, ENV rho_gb, ENV rho_lc){
	if(rho_lc!=NULL){
		if(strcmp(rho_lc->ID,chaine)==0){
            printf("trouve %s en position %p \n",chaine,rho_lc);
			return rho_lc;
        }
        else
            return rech2(chaine, rho_gb, rho_lc->SUIV);
	}

	else if(rho_gb!=NULL){
		if(strcmp(rho_gb->ID,chaine)==0){
            printf("trouve %s en position %p \n",chaine,rho_gb);
			return rho_gb;
        }
        else
            return rech2(chaine, rho_gb->SUIV, NULL);
	}

    else
        return NULL;
}

void inbilenv(BILENV *prho,char *var){

	ENV env = prho->debut;
    ENV pos = rech(var, env);

	if(pos == NULL){
        ENV new = creer_env(var, 0);
        new->SUIV=env;
		prho->debut = new;
    }

}

BILENV bilenv_vide(){
	BILENV bilenv;
	bilenv.debut = NULL;
	bilenv.fin = NULL;
    return bilenv;
}

BILENV creer_bilenv(ENV var){

	BILENV bilenv = bilenv_vide();
	bilenv.fin = bilenv.debut = var;
        bilenv.debut->SUIV = bilenv.fin->SUIV = NULL;
	return bilenv;

}

BILENV copier_bilenv(BILENV b){

	ENV copenv = copier_env(b.debut);
    b.debut = copenv;
    while(copenv && copenv->SUIV)
        copenv=copenv->SUIV;
    b.fin=copenv;
	return b;

}

BILENV concat(BILENV b1, BILENV b2){
    BILENV br;
    if (b1.fin != NULL){
        if (b2.debut != NULL){
            b1.fin->SUIV = b2.debut;
            br.debut = b1.debut;
            br.fin = b2.fin;
            return br;
        }
        else
            return b1;
    }
    else
        return b2;
}
void ecrire_bilenv(BILENV b){
    ENV e = b.debut;
    printf("Début BILENV\n");
    if (e != NULL)
        ecrire_env(e);
    printf("fin BILENV\n");
}
void affectb(BILENV rho_gb, BILENV rho_lc, char *lhs, int rhs) {
    //Recherche locale
    ENV local = rech(lhs, rho_lc.debut);
    if (local != NULL) {
        affect(local, lhs, rhs);
    }
    else{
        ENV global = rech(lhs, rho_gb.debut);
        //TODO : Gérer le cas ou la variable n'existe pas du tout
        affect(global, lhs, rhs);
    }
}
LFON copier_fon(LFON lfn){
    LFON fcopie = Lfonalloc();
    fcopie->ID = lfn->ID;
    fcopie->PARAM = copier_bilenv(lfn->PARAM);
    fcopie->VARLOC = copier_bilenv(lfn->VARLOC);
    //TODO : fonction copier_noe
    //fcopie->CORPS = copier_noe(lfn->CORPS);
    if (lfn->SUIV != NULL)
        fcopie->SUIV = copier_fon(lfn->SUIV);
    else
        (lfn->SUIV = NULL);
    return fcopie;
}
void ecrire_fon(LFON bfn){
    printf("Début de la fonction\n");
    printf("ID fonction : %s\n", bfn->ID);
    printf("Début Param : \n");
    ecrire_bilenv(bfn->PARAM);
    printf("Fin Param\n");
    printf("Début variables locales : \n");
    ecrire_bilenv(bfn->VARLOC);
    printf("Fin variables locales\n");
    printf("Début corps : \n");
    //TODO : ecrire_noe
    //ecrire_noe(bfn->CORPS);
    printf("Fin corps\n");
    if (bfn->SUIV != NULL){
        printf("Passage fonction suivante\n\n");
        ecrire_fon(bfn->SUIV);
    }
    else{
        printf("Pas de suivant\n");
    }
    printf("Fin de la fonction.\n");



}
LFON rechfon(char *chaine, LFON listident){
    if (strcmp(listident->ID, chaine) == 0)
        return listident;
    else if (listident->SUIV != NULL)
        return rech(chaine, listident->SUIV);
    else
        return NULL;
}
BILFON bilfon_vide()
{
    BILFON b;
    b.debut = b.fin = NULL;
    return b;
}
BILFON creer_bilfon(LFON pfon)
{
    BILFON b = bilfon_vide();
    b.debut = pfon;
    b.fin = b.debut;
    b.debut->SUIV = b.fin->SUIV = NULL;
    return b;
}
BILFON copier_bilfon(BILFON bfn)
{
    BILFON b = bilfon_vide();
    if (bfn.debut != NULL)
    {
        b = creer_bilfon(copier_fon(b.debut));
    }
    return b;

}
BILFON concatfn(BILFON bfn1, BILFON bfn2)
{
    BILFON b = bilfon_vide();
    if (bfn1.debut != NULL && bfn2.debut != NULL)
    {
        b.debut = bfn1.debut;
        bfn1.fin->SUIV = bfn2.debut;
        b.fin = bfn2.fin;
    }
    else if (bfn2.debut != NULL)
    {
        b.debut = bfn2.debut;
        b.fin = bfn2.fin;
    }
    else if (bfn1.debut != NULL)
    {
        b = bfn1;
    }
    return b;
}
BILENV allvars(BILFON bfon)
{
    BILENV params = bilenv_vide();
    BILENV varloc = bilenv_vide();
    if (bfon.debut != NULL)
    {
        LFON w = bfon.debut;
        while (w != NULL)
        {
            params = concat(params, w->PARAM);
            varloc = concat(varloc, w->VARLOC);
            w = w->SUIV;
        }
    }
    return concat(params, varloc);
}
void ecrire_bilfon(BILFON bfn)
{
    LFON w = bfn.debut;
    if (w == NULL)
        printf("vide");
    else
    {
        while(w != NULL)
        {
            printf("ID: %s ( ", w->ID);
            ecrire_bilenv(w->PARAM);
            printf(" )\n variables locales: \n");
            ecrire_bilenv(w->VARLOC);
            printf("\n");
            prefix(w->CORPS);
            w = w->SUIV;
        }
    }
    printf("\n");
}
void ecrire_prog(BILENV argb,BILFON argbf,NOE argno)
{
    printf("argb: \n");
    ecrire_bilenv(argb);
    printf("argbf: \n");
    ecrire_bilfon(argbf);
    printf("argno: \n");
    prefix(argno);
}/*
int main(int argc, char** argv)
{
    BILFON b = bilfon_vide();
    printf("bilfon_vide: doit etre vide: ");
    ecrire_bilfon(b);
    LFON lfon = malloc(sizeof(struct cellfon));
    lfon->ID = "test 1";
    LFON lfon2 = malloc(sizeof(struct cellfon));
    lfon2->ID = "test 2";
    LFON lfon3 = malloc(sizeof(struct cellfon));
    lfon3->ID = "test 3";
    lfon->SUIV = lfon2->SUIV = lfon3->SUIV = NULL;

    printf("creer_bilfon: doit avoir un élement (test 1): \n");
    b = creer_bilfon(lfon);
    ecrire_bilfon(b);
    lfon->SUIV = lfon2;
    printf("creer_bilfon: doit avoir 2 élement (test 1 -> test 2): \n");
    b = creer_bilfon(lfon);
    ecrire_bilfon(b);

    printf("copier_bilfon: (en attente de copier_fon ");
    BILFON b2 = copier_bilfon(b);
    ecrire_bilfon(b2);
    printf("debut: %p == %p  et fin: %p == %p\n", b.debut, b2.debut, b.fin, b2.fin);

    b2 = creer_bilfon(lfon3);
    printf("concatfn:  doit avoir 3 élements (test1->test2->test3): \n");
    b = concatfn(b,b2);
    ecrire_bilfon(b);
}
*/
