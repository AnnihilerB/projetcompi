#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>	
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
char * TAB;

char *concats(const char *s1, const char *s2){
	char *res = malloc(strlen(s1) + strlen(s2) +1);
	if(res){
		strcpy(res, s1);
		strcat(res,s2);
	}
	return res;
}

void interpreteurC3A(BILQUAD bilist){
	printf("DEBUT\n");
	presentquad = bilist.debut;

	ENV environnement = Envalloc();
	environnement->ID = Idalloc();
	environnement->SUIV = NULL;

	ENV envfonction = Envalloc();
	envfonction->ID = Idalloc();
	envfonction->SUIV = NULL;

	ENV envtab = Envalloc();
	envtab->ID = Idalloc();
	envtab->SUIV = NULL;

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
			printf("lapin PL MO MU\n");
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
			printf("lapin AF\n");
			if(rech(ARG1, environnement)==NULL)
				initenv(&environnement, ARG1);
			affect(environnement, ARG1, valch(environnement, ARG2));
		}

		else if(operator == AFC){
			printf("lapin AFC\n");
			affect(environnement, RES, atoi(ARG1));
		}

		else if(operator == ST){
			printf("lapin ST\n");
			break;
		}

		else if(operator == SK){
			printf("lapin SK\n");
			if(RES!=NULL){
				if(rech(RES, environnement)==NULL){
					initenv(&environnement, RES);
					affect(environnement, RES, 0);
				}
			}
		}

		else if(operator==AND || operator==OR || operator==LT){
			printf("lapin AND OR LT\n");
			if(isdigit(atoi(ARG1)))
				val1 = atoi(ARG1);
			else
				val1 = valch(environnement, ARG1);

			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);

			if(operator==AND){
				printf("lapin AND\n");
				if(val1 && val2)
					result = 1;
				else
					result = 0;
			}

			if(operator==OR){
				printf("lapin OR\n");
				if(val1||val2)
					result = 1;
				else
					result = 0;
			}

			if(operator==LT){
				printf("lapin LT\n");
				if(val1 < val2)
					result = 1;
				else
					result = 0;	
			}

			affect(environnement, RES, result);
		}

		else if(operator==NOT){

			printf("lapin NOT\n");

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
			printf("lapin JP\n");
			presentquad = rechbq(RES, bilist);
		}

		else if(operator==JZ){
			printf("lapin JZ\n");
			if(valch(environnement, ARG1)==0){
				presentquad = rechbq(RES, bilist);
			}
		}

		else if(operator==IND){
			printf("lapin IND\n");
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else{
				val2 = valch(environnement, ARG2);
				sprintf(ARG2, "%d", val2);
			}

			TAB = concats(ARG1, ARG2);

			valtab = valch(envtab, TAB);
			affect(environnement, TAB, valtab);
		}

		else if(operator==AFIND){
			printf("lapin AFIND\n");
			if(isdigit(atoi(ARG2)))
				val2 = atoi(ARG2);
			else
				val2 = valch(environnement, ARG2);
				sprintf(ARG2, "%d", val2);

			TAB = concats(ARG1, ARG2);

			if(rech(TAB, envtab)==NULL)	
				initenv(&environnement, TAB);
			else
				affect(envtab, TAB, valtab);	

		}

		else if(operator==PARAM){
			printf("lapin PARAM\n");
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
			printf("lapin CALL\n");
			callquad=presentquad;
			nparam = atoi(ARG2);
			presentquad=rechbq(ARG1, bilist);


		}

		else if(operator==RET){
			printf("lapin RET\n");
			presentquad=callquad->SUIV;

		}

		if(operator!=JZ && operator!=JP){
			presentquad=presentquad->SUIV;
		}

	}
	ecrire_env(environnement);
}