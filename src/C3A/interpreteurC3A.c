#include <string.h>
#include <ctype.h>
#include "bilquad.h"
#include "environ.h"
#include "interpreteurC3A.h"
#include "traducteurC3A.h"

BILQUAD bilist;
QUAD quad; 
QUAD presentquad; 
QUAD callquad;
int operator;
char * ETIQ;
char * ARG1; 
char * ARG2;
char * RES;

void interpreteurC3A(BILQUAD bilist){

	presentquad = bilist.debut;

	ENV environnement = Envalloc();
	environnement->ID = Idalloc();
	environnement->SUIV = NULL;

	ENV envfonction = Envalloc();
	envfonction->ID = Idalloc();
	envfonction->SUIV = NULL;

	int val1;
	int val2;
	int result;
	int nparam;

	ecrire_bilquad(bilist);

	while(presentquad != NULL){

		operator = presentquad->OP;
		ARG1 = presentquad->ARG1;
		ARG2 = presentquad->ARG2;
		RES = presentquad->RES;
		initenv(&environnement, RES);

		if(operator==PL||operator==MO||operator==MU){
			if(isdigit(atoi(ARG1)))
				val1 = atoi(ARG1);
			else
				val1 = valch(environnement, ARG1);
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);
			result = eval(operator, val1, val2);
			affect(environnement, RES, result);
		}

		else if(operator == AF){
			if(rech(ARG1, environnement)==NULL)
				initenv(&environnement, ARG1);
			affect(environnement, ARG1, valch(environnement, ARG2));
		}

		else if(operator == AFC)
			affect(environnement, RES, atoi(ARG1));


		else if(operator == ST){
			break;
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

		else if(operator==JP){
			presentquad = rechbq(RES, bilist);
		}

		else if(operator==JZ){
			if(valch(environnement, ARG1)==0){
				presentquad = rechbq(ARG1, bilist);
			}
		}

		else if(operator==IND){

		}

		else if(operator==AFIND){

		}

		else if(operator==PARAM){

			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			if(rech(envfonction, ARG1)==NULL)
				initenv(&environnement, ARG1);
			else
				affect(envfonction, ARG1, val2);
		}

		else if(operator==CALL){
			callquad=presentquad;
			nparam = atoi(ARG2);
			presentquad=rechbq(ARG1, bilist);


		}

		else if(operator==RET){
			presentquad=callquad->SUIV;
		}

		if(operator!=JZ && operator!=JP){
			presentquad=presentquad->SUIV;
		}

	}
	ecrire_env(environnement);
}