%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "analyseur.h"
    #include "util.h"
    int yyerror(char* s);
    int yylex();
%}

%union{
        EnvGlobal envG;
        BILFON fOUp;
        BILENV varG;
        NOE noe;
        int val;
        char* nom;
}
%start MP
%token T_boo T_int Def Dep Af true false Se If Th El Var Wh Do Pl Mo Mu And Or Not Lt Eq Sk NFon NPro NewAr I V T_ar

%type <fOUp> LD
%type <envG> MP
%type <varG> L_vart
%type <noe> C
%left Se
%left Pl Mo Mu And Or Not Lt Eq
%left Sk /*????*/
%right Wh If V /*????*/

%%
MP: L_vart LD C  {  printf("T_ar = %d T_bool = %d T_int = %d\n", T_ar, T_boo, T_int);
                    $$=creer_environnementGlobal();
                    //$$->variablesGlobales = $1;
                    $$->listeDesFonctionsOuProcedure = $2;
                    //$$->corpsGlobale = $3;
                }
    ;
E: E Pl E {}
    | E Mo E {}
    | E Mu E {}
    | E Or E {}
    | E Lt E {}
    | E Eq E {}
    | E And E {}
    | Not E {}
    | '(' E ')' {}
    | I {}
    | V {}
    | true {}
    | false {}
    | V '(' L_args ')' {}
    | NewAr TP '[' E ']' {}
    | Et {}
    ;
Et: V '[' E ']' {}
    | Et '[' E ']' {}
    ;
C: C Se C {}
    | Et Af E {}
    | V Af E {}
    | Sk {}
    | '{' C '}' {}
    | If E Th C El C {}
    | Wh E Do C {}
    | V '(' L_args ')' {}
    | %empty {}
    ;
L_args: %empty {}
    | L_argsnn {}
    ;
L_argsnn: E {}
    | E ',' L_argsnn {}
    ;
L_argt: %empty {}
    | L_argtnn {}
    ;
L_argtnn: Argt {}
    | L_argtnn ',' Argt {}
    ;
Argt: V ':' TP {}
    ;
TP: T_boo {}
    | T_int {}
    | T_ar TP {}
    ;
L_vart: %empty {}
    | L_vartnn {}
    ;
L_vartnn: Var Argt {;}
    | L_vartnn ',' Var Argt {;}
    ;
D_entp: Dep NPro '(' L_argt ')' {}
    ;
D_entf: Def NFon '(' L_argt ')' ':' TP {}
    ;
D: D_entp L_vart C {}
    | D_entf L_vart C {}
    ;
LD: %empty {}
    | LD D {$$ = bilfon_vide();}
    ;


%%

int yyerror(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
int yywrap()
{
    return -1;
}
int main(int argn, char** argv)
{
    yyparse();
    return 0;
}
