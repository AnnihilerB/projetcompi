#include "util.h"
#include "analyseur.h"
#include "ppascal.tab.h"

void interpreteur(NOE corps){

  switch (corps->codop){
    case I:
      return atoi(corps->ETIQ);
    case V:
      break;
    case NFON:
      break;
    case Af:
      if (corps->FG->codop == V)
        //VARIABLES
      if (corps->FG->codop == T_ar)
        //tableaux
      break;
    case Pl: case Mo: case Mu: case And: case Or: case Not: case Lt: case Eq:
      return eval(corps->codop, interpreteur(corps->FG), interpreteur(corps->FD));
    case Se:
      interpreteur(corps->FG);
      interpreteur(corps->FD);
      return 0;
  }

}

int eval(int op, int a, int b){
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
    case Not:
      return 
  }
}
