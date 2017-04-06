#include "tableau.h"

void affecter_valeur(TAB *tableau, int index, int valeur){
    tableau->tab[index] = valeur;
}

TAB creer_tableau(int dimension, int taille){
    struct tableau *tab = malloc(sizeof(struct tableau));
    tab->tab = malloc(taille * sizeof(int));
    tab->FG = NULL;
    return tab;
}

int recuperer_valeur(TAB* tableau, int index){
    return tableau->tab[index;
}