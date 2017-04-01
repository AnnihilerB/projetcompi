#include "util.h"
#include "analyseur.h"
#include "ppascal.tab.h"
#include <string.h>
#include <stdio.h>

EnvGlobal envG;
ENV e;

void interpreteur(EnvGlobal env){
  envG = env;
  interp_rec(envG->corpsGlobale);
}

int interp_rec(NOE corps){
  switch (corps->codop){
    case I:
      return atoi(corps->ETIQ);
    case V:
       e = rech2(corps->ETIQ, envG->variablesGlobales.debut, envG->variablesGlobales.debut);
       //fprintf(stdout, "Type variable : %s, val : %d\n", e->ID, e->VAL);
       return e->VAL;
      break;
    case NFon:
      break;
    case Af:
      fprintf(stdout, "Af\n");
      if (corps->FG->codop == V){
        //Variable classique
        printf("FG : %s\n", corps->FG->ETIQ);
        printf("FD : %s\n", corps->FD->ETIQ);
        affectb(envG->variablesGlobales, envG->variablesGlobales, corps->FG->ETIQ, interp_rec(corps->FD));
      }
      if (corps->FG->codop == T_ar)
        //tableaux
      break;
    case Pl: case Mo: case Mu: case And: case Or: case Not: case Lt: case Eq:
      return evaluation(corps->codop, interp_rec(corps->FG), interp_rec(corps->FD));
    case Se:
      fprintf(stdout, "SE\n");
      interp_rec(corps->FG);
      interp_rec(corps->FD);
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
      printf("MU\n");
      return a * b;
      break;
    case And:
      return a && b;
      break;
    case Or:
      return a || b;
      break;
    case Not:
      break;
  }
}
