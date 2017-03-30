/** Ce fichier est conçu pour tester pour tester les fonctions de
* util.c allant de :
  extern BILENV concat(BILENV b1, BILENV b2) à
  extern LFON rechfon(char *chaine, LFON listident) inclus.
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

#define NBENV 4

BILENV b1;
BILENV b2;
LFON lfon;
LFON lfonSuiv;
NOE corps;
bool success = true;

void erreur(char *nomFonction, char *message){
  fprintf(stderr, "Erreur ! %s : %s\n", nomFonction, message);
}

bool testConcatBilenv(){
  BILENV conc = concat(b1, b2);
  if (conc.debut == NULL){
    erreur("concat", "Element debut NULL");
    return false;
  }
  int nbEnv = 0;
  ENV e = conc.debut;
  while (e != NULL){
    nbEnv++;
    e = e->SUIV;
  }
  if (nbEnv != NBENV){
    erreur("concat", "Nombre d'élements non corrects");
    fprintf(stderr, "Attendu %d, effectif : %d\n", NBENV, nbEnv);
    return false;
  }
  return true;
}

bool testAffectb(){
  //b1 joue le role de global et b2 de local;
  int valglobal = 42;
  int vallocal = 43;
  //Affectation à la variable var2 locale la valeur 42
  affectb(b1, b2, "VAR2", vallocal);
  ENV e1 = b1.fin;
  //Vérfication que la valeur globale n'est pas modifiée.
  if (e1->VAL != 2){
    erreur("affectb", "Mauvais environnement modifié");
    fprintf(stderr, "Env global modifié au lieu du local.\n");
    return false;
  }
  //Vérification que la valeur locale a changée.
  ENV e2 = b2.debut;
  if (e2->VAL != vallocal){
    erreur("affectb", "Valeur locale non modifiée");
    return false;
  }

  affectb(b1, b2, "VAR1", valglobal);
  e1 = b1.debut;
  if (e1->VAL != valglobal){
    erreur("affectb", "Valeur globale non modifiée");
    return false;
  }
  return true;
}

bool testCopierFon(){
  int adresseLfon = lfon;
  int adresseLfonSuiv = lfonSuiv;
  LFON fonCopie = copier_fon(lfon);

  if (fonCopie == adresseLfon){
    erreur("copierFon", "Adresse de la copie identique à originale");
    return false;
  }
  if (fonCopie->SUIV == adresseLfonSuiv){
    erreur("copierFon", "Adresse de la copie du suivant identique à l'originale");
    return false;
  }
  if (fonCopie->CORPS == lfon->CORPS){
    erreur("copierFon", "Adresse de la copie du corps identique à l'originale");
    return false;
  }
  if (&fonCopie->PARAM == &lfon->PARAM){
    erreur("copierFon", "Adresse de la copie des params identique à l'originale");
    return false;
  }
  if (&fonCopie->VARLOC == &lfon->VARLOC){
    erreur("copierFon", "Adresse de la copie de varloc identique à l'originale");
    return false;
  }

  ecrire_fon(fonCopie);
  return true;
}

int main(int argc, char const *argv[]) {
  ENV e1 = creer_env("VAR1", 1); //b1.debut
  ENV e2 = creer_env("VAR2", 2); //b1.fin

  ENV e3 = creer_env("VAR2", 3); //b2.debut
  ENV e4 = creer_env("VAR4", 4); //b2.fin

  //Création des biliste d'ENV
  e1->SUIV = e2;
  b1.debut = e1;
  b1.fin = e2;

  e3->SUIV = e4;
  b2.debut = e3;
  b2.fin = e4;

  //Création des bilistes de fonctions
  lfon = Lfonalloc();
  lfonSuiv = Lfonalloc();
  corps = Nalloc();

  lfon->CORPS = corps;
  lfon->PARAM = b1;
  lfon->VARLOC = b2;
  lfon->SUIV = lfonSuiv;



  success = success && testCopierFon();
  success = success && testAffectb();
  success = success && testConcatBilenv();

  if (success){
    printf("Test passed ! \n");
  }
  return 0;
}
