/** Module de manipulation de tableau pour l'interpréteur PP **/

#include "environ.h"
#include "util.h"

typedef struct tableau{
    int *tab;
    TAB *FG;
}*TAB;

//Affecte dans tableau la valeur dasn la case index
void affecter_valeur(TAB *tableau, int index, int valeur);
//creer un tableau à n dimension, de taille taille
TAB creer_tableau(int dimension, int taille);
//renvoie la valeur dans tableau à index
int recuperer_valeur(TAB* tableau, int index);