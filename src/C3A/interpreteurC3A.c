#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>	
#include "bilquad.h"
#include "environ.h"
#include "interpreteurC3A.h"
#include "traducteurC3A.h"
#include "tableau.h"

BILQUAD bilist;
QUAD quad; 
QUAD presentquad; 
QUAD callquad;
int operator;
char * ETIQ;
char * ARG1; 
char * ARG2;
char * RES;
BILTAB bilisttab;
TAB tableau;

void interpreteurC3A(BILQUAD bilist){
	
	presentquad = bilist.debut;

	ENV environnement = Envalloc();
	environnement->ID = Idalloc();
	environnement->SUIV = NULL;

	ENV envfonction = Envalloc();
	envfonction->ID = Idalloc();
	envfonction->SUIV = NULL;

	bilisttab = biltab_vide();

	int val1;
	int val2;
	int valtab;
	int result;
	int nparam;

	ecrire_bilquad(bilist);

	while(presentquad != NULL){

		operator = presentquad->OP;
		ARG1 = presentquad->ARG1;
		ARG2 = presentquad->ARG2;
		RES = presentquad->RES;

		if(RES!=NULL){
			if(operator != JP && operator != JZ){
				if(rech(RES, environnement)==NULL)
					initenv(&environnement, RES);
			}
		}
	
		if(operator==PL||operator==MO||operator==MU){
		
			if(isdigit(atoi(ARG1)))
				val1 = atoi(ARG1);
			else
				val1 = valch(environnement, ARG1);
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			if(operator==PL)
				result = val1 + val2;
			else if(operator==MO)
				result = val1 - val2;
			else if(operator==MU)
				result = val1 * val2;
			affect(environnement, RES, result);
		}

		else if(operator == AF){
			
			if(rech(ARG1, environnement)==NULL)
				initenv(&environnement, ARG1);
			affect(environnement, ARG1, valch(environnement, ARG2));
		}

		else if(operator == AFC){
			
			affect(environnement, RES, atoi(ARG1));
		}

		else if(operator == ST){
			
			break;
		}

		else if(operator == SK){
			
			if(RES!=NULL){
				if(rech(RES, environnement)==NULL){
					initenv(&environnement, RES);
					affect(environnement, RES, 0);
				}
			}
		}

		else if(operator==AND || operator==OR || operator==LT){
			
			if(isdigit(atoi(ARG1)))
				val1 = atoi(ARG1);
			else
				val1 = valch(environnement, ARG1);

			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			if(operator==AND){
	
				if(val1 && val2)
					result = 1;
				else
					result = 0;
			}

			if(operator==OR){
				
				if(val1||val2)
					result = 1;
				else
					result = 0;
			}

			if(operator==LT){
				
				if(val1 < val2)
					result = 1;
				else
					result = 0;	
			}

			affect(environnement, RES, result);
		}

		else if(operator==NOT){

			if(isdigit(atoi(ARG1)))
				val1 = atoi(ARG1);
			else
				val1 = valch(environnement, ARG1);
			if(val1==1)
				result=0;
			else
				result=1;
			affect(environnement, RES, result);
		}							

		else if(operator==JP)
			presentquad = rechbq(RES, bilist);

		else if(operator==JZ){
	
			if(valch(environnement, ARG1)==0){
				presentquad = rechbq(RES, bilist);
			}
		}

		else if(operator==IND){ //on ajoute à la variable destination la valeur de ARG1[ARG2]
			
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			tableau=rechercher_tableau(ARG1, bilisttab);			
			result= lire_tableau(tableau, val2);
			affect(environnement, RES, result);
		}

		else if(operator==AFIND){

			if(strcmp(ARG1,ARG2)==0){ //Si le tableau n'existe pas.
				if(isdigit(atoi(RES)))
					result = atoi(RES);
				else
					result = valch(environnement, RES);

				tableau = creer_tableau(ARG1, result);
				ajouter_tableau(&bilisttab, tableau);
			}

			else{ //Si on veut ajouter la valeur de destination dans le tableau

				if(isdigit(atoi(ARG2)))
					val2 = atoi(ARG2);
				else
					val2 = valch(environnement, ARG2);	
				result = valch(environnement, RES);
				tableau=rechercher_tableau(ARG1, bilisttab);
				ecrire_tableau(tableau, val2, result);
			}
		}

		else if(operator==PARAM){
	
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			if(rech(ARG1, envfonction)==NULL)
				initenv(&environnement, ARG1);
			else
				affect(envfonction, ARG1, val2);
		}

		else if(operator==CALL){

			callquad=presentquad;
			nparam = atoi(ARG2);
			presentquad=rechbq(ARG1, bilist);
		}

		else if(operator==RET)
			presentquad=callquad->SUIV;

		if(operator!=JZ && operator!=JP && operator!=CALL && operator!=RET)
			presentquad=presentquad->SUIV;

	}
	ecrire_env(environnement);
}