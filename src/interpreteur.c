#include "util.h"
#include "analyseur.h"
#include "ppascal.tab.h"
#include "tableau.h"
#include <string.h>
#include <stdio.h>

EnvGlobal envG; // Environnement du programme -> Var globale, listes des fonctions, coprs du programme principal.
ENV varEnv; //Env stockant la variable courante.
LFON fonctionCourante; //Fonction à éxecuter si appel de fonctions.
BILENV paramFonctions; //Paramètre d'un appel de fonctions interprétés.
int dansFonction = 0; //Indicateur dans fonction

ENV cpy; //Environnement de copie lors d'un AF


TAB t; // Tableau
BILTAB biltab;
TAB TEST;



void interpreteur(EnvGlobal env){
  envG = env;
  biltab = biltab_vide();
  interp_rec(envG.corpsGlobale);
}

void interp_args(NOE fonction, BILENV param, BILENV *paramFonctions){
  NOE paramAppel = fonction->FG; //Liste lors de l'appel de fonctions
  ENV paramFormel = param.debut; //Liste des paramètres formels -> Nom des paramètres lors de la déclaration.

  varEnv = Envalloc();
  varEnv->ID = Idalloc();
  varEnv->SUIV = NULL;

  while(paramFormel != NULL){ 
    if (paramFormel->ID != NULL){ //Dans le cas d'une fonction le premier paramètre est null.
      int res = interp_rec(paramAppel->FD); //Résultat de l'interprétation du fils droit -> appel du paramètre.

      ENV p = Envalloc(); //Env stockant la valeur de l'interprétation du fils droit
      p->ID = Idalloc();
      p->ID = paramFormel->ID; //Nom du fils droit à stocker.
      p->SUIV = NULL;

      affect(p, paramFormel->ID, res); //Affectation de la valeur.

      //Stockage dans la liste contenant les paramètre de fonctions interprétés.
      if (paramFonctions->debut == NULL){
        *paramFonctions = bilenv_vide();
        paramFonctions->debut = paramFonctions->fin = p;
      }
      else{
        paramFonctions->fin->SUIV = p;
        paramFonctions->fin = p;
      }
      paramAppel=paramAppel->FG; //Progression de l'arbre de paramètre.
    }
    paramFormel = paramFormel->SUIV; //progression de la liste des noms de paramètres.
  }
}

int interp_rec(NOE corps){
  switch (corps->codop){
    /* ---------- Cas de base (minimaux) ---------- */
    case T_boo:
      if (strcmp(corps->ETIQ, "true") == 0)
        return 1; //True
      return 0; // False
    case I:
      if (corps->ETIQ[0] == '-'){
        int nb = atoi( (corps->ETIQ) +1 );
        return -nb;
      }
      return atoi(corps->ETIQ);
    case V:
      if (corps->FG != NULL && corps->FD != NULL){ //La variable est un tableau.
        t = rechercher_tableau(corps->FG->ETIQ, biltab); //Récupération du tableau
        return lire_tableau(t, atoi(corps->FD->ETIQ)); //REnvoie la valeur du tableau dans la case corps->FD->ETIQ
        break;
      }

      if (dansFonction){ // Dans un appel de fonctions.
        varEnv = rech2(corps->ETIQ, fonctionCourante->VARLOC.debut, paramFonctions.debut); //Priorité de la recherche sur la liste de paramètre.
        if (varEnv == NULL){
          //Variable non trouvé dans param ou locales donc recheche globale.
          varEnv = rech2(corps->ETIQ, envG.variablesGlobales.debut, envG.variablesGlobales.debut);
        }
        if (varEnv == NULL){
          //Variable pas présente du tout donc valeur de retour.
          varEnv = Envalloc();
          varEnv->ID = Idalloc();
          strcpy(varEnv->ID, corps->ETIQ);
        }
      }
      else{
        //Hors fonction ou a
        varEnv = rech2(corps->ETIQ, envG.variablesGlobales.debut, envG.variablesGlobales.debut);
      }
      return varEnv->VAL;
      break;

    case NewAr:
        t = creer_tableau(varEnv->ID, atoi(corps->FD->ETIQ)); // Créé un tableau don le nom est varEnv, de taille FD->ETIQ
        ajouter_tableau(&biltab, t); //AJoute le tableau au BILTAB
        break;   

    /* ---------- Cas composés ---------- */
    case NPro: case NFon:
      dansFonction = 1; // Indicateur de rentrée dans fonction
      fonctionCourante = rechercher_lfon(corps->ETIQ, envG.listeDesFonctionsOuProcedure.debut); //Recherche le LFON de la fonction courante.
      interp_args(corps, fonctionCourante->PARAM, &paramFonctions); //Interprétation de la liste des args lors de l'appel.
      interp_rec(fonctionCourante->CORPS); //Interprétation de la fonction
      dansFonction = 0; //Sortie de fonction.
      return varEnv->VAL; //Envoie de la valeur de retour
      break;
      
    case Af:
      if (corps->FG->FG != NULL && corps->FG->FD != NULL && corps->FG->codop == V){ //Un des deux memebres est un tableau.
        //Vérifie si le membre gauche est un tableau
        t = rechercher_tableau(corps->FG->ETIQ, biltab);
        if (t != NULL){
          ecrire_tableau(t, interp_rec(corps->FG->FD) , interp_rec(corps->FD)); //Ecriture de la valeur dans la case
        }
        break;
      }
      else if (corps->FG->codop == V){ //Membre droit variable/valeur/tableau
        //Variable classique
        interp_rec(corps->FG); //Interp pour stocker dans varEnv l'ENV de la variable.
        cpy = Envalloc();
        cpy = varEnv; // Garde une trace de la variable pour éviter réécriture par interp FD.
        affect(cpy, cpy->ID, interp_rec(corps->FD));
        break;
      }
    case Pl: case Mo: case Mu: case And: case Or: case Lt: case Eq:
      return evaluation(corps->codop, interp_rec(corps->FG), interp_rec(corps->FD));
    case Not:
      if (interp_rec(corps->FD) == true) //Inversion
        return false;
      else
        return true;
    case Se:
      interp_rec(corps->FG); //Interprétage Gauche puis Droit.
      interp_rec(corps->FD);
      return 0;
    case Sk:
      return 0;
    case Wh:
      while (interp_rec(corps->FG))
        interp_rec(corps->FD);
      return 0;
    case If:
      if (interp_rec(corps->FG))
        interp_rec(corps->FD->FG);
      else
        interp_rec(corps->FD->FD);
      return 0;
  }  
}

int evaluation(int op, int a, int b){
  switch (op) {
    case Pl:
      return a + b;
      break;
    case Mo:
      return a - b;
      break;
    case Mu:
      return a * b;
      break;
    case And:
      return a && b;
      break;
    case Or:
      return a || b;
      break;
    case Lt:
      return a < b;
      break;
    case Eq:
      return a == b;
  }
}
