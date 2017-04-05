#include "util.h"
#include "analyseur.h"
#include "ppascal.tab.h"
#include <string.h>
#include <stdio.h>

EnvGlobal envG;
ENV e;
LFON fonctionCourante;
int dansFonction = 0;

void interpreteur(EnvGlobal env){
  envG = env;
  interp_rec(envG->corpsGlobale);
}

int interp_rec(NOE corps){
  switch (corps->codop){
    case T_boo:
      if (strcmp(corps->ETIQ, "true") == 0)
        return 1;
      return 0;
    case I:
      return atoi(corps->ETIQ);
    case V:
      if (dansFonction){
        e = rech2(corps->ETIQ, fonctionCourante->VARLOC.debut, fonctionCourante->PARAM.debut);
        if (e == NULL)
          e = rech2(corps->ETIQ, envG->variablesGlobales.debut, envG->variablesGlobales.debut);
      }
      else{
        e = rech2(corps->ETIQ, envG->variablesGlobales.debut, envG->variablesGlobales.debut);
      }
      return e->VAL;
      break;
    case NFon:
      dansFonction = 1;
      fonctionCourante = rechercher_lfon(corps->ETIQ, envG->listeDesFonctionsOuProcedure.debut);
      break;
    case Af:
      if (corps->FG->codop == V){
        //Variable classique
        affectb(envG->variablesGlobales, envG->variablesGlobales, corps->FG->ETIQ, interp_rec(corps->FD));
      }
      if (corps->FG->codop == T_ar)
        //tableaux
      break;
    case Pl: case Mo: case Mu: case And: case Or: case Lt: case Eq:
      return evaluation(corps->codop, interp_rec(corps->FG), interp_rec(corps->FD));
    case Not:
      if (interp_rec(corps->FD) == true)
        return false;
      else
        return true;
    case Se:
      interp_rec(corps->FG);
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
