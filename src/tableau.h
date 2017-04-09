/** Module de gestion des tableaux à 1D **/

typedef struct caseTableau{
    int indice;
    int val; 
    struct caseTableau *SUIV;
}*CASE;

typedef struct tableau{
    char *nom;
    int taille;
    CASE debut;
    struct tableau *SUIV;
}*TAB;

typedef struct{
    TAB debut;
    TAB fin;
}BILTAB;

//Affiche le tableau t.
void affichertab(TAB t, int taille);

//Créé une instance de caseTableau.
CASE creer_caseTableau(int indice);

//Créé un tableau
TAB creer_tableau(char *nom, int n);

//Recherche dans la biliste de tableau, le tableau étiquété nom.
TAB rechercher_tableau(char *nom, BILTAB bil);

//Créé une biliste vide.
BILTAB biltab_vide();

//Ajoute un tableau à la biliste.
void ajouter_tableau(BILTAB *bil, TAB t);

//retourne la valeur à la case indice
int lire_tableau(TAB t, int indice);

//Ecrit val dans la case indice.
void ecrire_tableau(TAB t, int indice, int val);
