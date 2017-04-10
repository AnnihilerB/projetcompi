#include "tableau.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void affichertab(TAB t, int taille){
    CASE c = t->debut;
    for (int i = 0; i < taille; i++){
        printf("elem %d, indice : %d, val : %d\n", i, c->indice, c->val);
        c = c->SUIV;
    }
}

CASE creer_caseTableau(int indice){
    struct caseTableau *caseT = malloc(sizeof(struct caseTableau));
    caseT->indice = indice;
    caseT->val = 0;
    caseT->SUIV = NULL;
    return caseT;
}

TAB creer_tableau(char *nom, int n){
    //Création de la première case du tableau;
    struct tableau *tab = malloc(sizeof(struct tableau));
    tab->nom = nom;
    tab->taille = n;
    tab->debut = creer_caseTableau(0);
    tab->SUIV = NULL;
    CASE c = tab->debut;
    //Création des cases suivantes.
    for (int i = 1; i < n; i++){
        c->SUIV = creer_caseTableau(i);
        c = c->SUIV;
    }
    return tab;
}

TAB rechercher_tableau(char *nom, BILTAB bil){
    TAB t = bil.debut;
    while (t != NULL){
        if (strcmp(t->nom, nom) == 0){
            return t;
        }
        t = t->SUIV;
    }
    return NULL;
}

BILTAB biltab_vide(){
    BILTAB bil;
    bil.debut = NULL;
    bil.fin = NULL;
    return bil;
}

void ajouter_tableau(BILTAB *bil, TAB t){
    if (bil->debut == NULL){ //premier tableau
        bil->debut = bil->fin = t;
    }
    else{ //plusieurs tableaux
        bil->fin->SUIV = t; //Lie au précédent
        bil->fin = t; //Fin de liste
    }
}

int lire_tableau(TAB t, int indice){
    CASE c = t->debut;
    while(c->indice != indice){ //Recherche du bon indice
        c = c->SUIV;
    }
    return c->val;
}

void ecrire_tableau(TAB t, int indice, int val){
    CASE c = t->debut;
    while(c->indice != indice) //Recherche du bon indice.
        c = c->SUIV;
    c->val = val;
}
