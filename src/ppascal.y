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
        LFON fon;
        ENV env;
        NOE noe;
        int val;
        char* nom;
}
%start MP
%token T_boo T_int Def Dep Af true false Se If Th El Var Wh Do Pl Mo Mu And Or Not Lt Eq Sk NFon NPro NewAr I V T_ar

%type <fOUp> LD
%type <envG> MP
%type <varG> L_argt L_argtnn L_vart L_vartnn
%type <noe> C E Et Ca L_args L_argsnn TP 
%type <env> Argt
%type <fon> D_entp D_entf D
%left Se
%left Pl Mo Mu And Or Not Lt Eq
%left Sk /*????*/
%right Wh If V /*????*/

%%
//TODO: vérification de type
MP: L_vart LD C  {  
                    $$=creer_environnementGlobal($1, $2, $3);
                    $$->variablesGlobales = $1;
                    $$->listeDesFonctionsOuProcedure = $2;
                    $$->corpsGlobale = $3;
                    printf("test: %p et %p\n", $$->variablesGlobales.debut, $$->variablesGlobales.fin);
                    ecrire_prog($$->variablesGlobales, $$->listeDesFonctionsOuProcedure, $$->corpsGlobale);
                }
    ;
E: E Pl E {$$ = Nalloc(); $$->FG = $1; $$->codop = Pl; $$->FD =  $3;}
    | E Mo E {$$ = Nalloc(); $$->FG = $1; $$->codop = Mo; $$->FD =  $3;}
    | E Mu E {$$ = Nalloc(); $$->FG = $1; $$->codop = Mu; $$->FD =  $3;}
    | E Or E {$$ = Nalloc(); $$->FG = $1; $$->codop = Or; $$->FD =  $3;}        
    | E Lt E {$$ = Nalloc(); $$->FG = $1; $$->codop = Lt; $$->FD =  $3;}        
    | E Eq E {$$ = Nalloc(); $$->FG = $1; $$->codop = Eq; $$->FD =  $3;}        
    | E And E {$$ = Nalloc(); $$->FG = $1; $$->codop = And; $$->FD =  $3;}      
    | Not E {$$ = Nalloc(); $$->FD = $2;}
    | '(' E ')' {$$ = $2;}
    | I {$$ = Nalloc(); $$->codop = I; $$->ETIQ = yylval.nom;}
    | V {$$ = Nalloc(); $$->codop = V; $$->ETIQ = yylval.nom;}
    | true {$$ = Nalloc(); $$->codop = true;}
    | false {$$ = Nalloc(); $$->codop = false;}
    | V '(' L_args ')' {NOE v = Nalloc(); v->codop = NFon; v->ETIQ = yylval.nom; $$ = v; $$->FG = $3; $$->FD = NULL;}
    | NewAr TP '[' E ']' {$$ = Nalloc(); $$->codop = NewAr; $$->FG = $2; $$->FD = $4;}
    | Et {$$ = $1;}
    ;
Et: V '[' E ']' {NOE v = Nalloc(); v->codop = V; v->ETIQ = yylval.nom; $$ = Nalloc(); $$->codop = V; $$->FG = v; $$->FD = $3;}
    | Et '[' E ']' {$$ = Nalloc(); $$->FG = $1; $$->FD = $3;}
    ;
C: C Se Ca {$$ = Nalloc(); $$->FG = $1; $$->codop = Se; $$->FD = $3;}
    | Sk {$$ = Nalloc(); $$->codop = Sk;}
    | '{' C '}' {$$ = $2;}
    | V '(' L_args ')' {NOE v = Nalloc(); v->codop = NFon; v->ETIQ = yylval.nom; $$ = v; $$->FG = $3; $$->FD = NULL;}
    | Ca {$$ = $1;}
    ;

Ca: Wh E Do Ca {$$ = Nalloc(); $$->codop = Wh; $$->FG = $2; $$->FD = $4;}
  | If E Th C El Ca {$$ = Nalloc(); $$->codop = If; $$->FG = $2; NOE noeVide = Nalloc(); noeVide->FG = $4; noeVide->FD = $6; $$->FD = noeVide;}
  | Et Af E {$$ = Nalloc(); $$->codop = Af; $$->FG = $1; $$->FD = $3;}
  | V Af E {NOE v = Nalloc(); v->codop = V; v->ETIQ = yylval.nom; $$ = Nalloc(); $$->codop = Af; $$->FG = v; $$->FD = $3;}
  | V '(' L_args ')' {NOE v = Nalloc(); v->codop = NFon; v->ETIQ = yylval.nom; $$ = v; $$->FG = $3; $$->FD = NULL;}
  ;
L_args: %empty {$$ = NULL;}
    | L_argsnn {$$ = $1;}
    ;
L_argsnn: E {$$ = $1;}
    | E ',' L_argsnn {$$ = $1; $$->FG = $3;}
    ;
L_argt: %empty {$$ = bilenv_vide();}
    | L_argtnn {$$ = $1;}
    ;
L_argtnn: Argt {$$ = creer_bilenv($1);}
    | L_argtnn ',' Argt {$$ = concat($1, creer_bilenv($3));}
    ;
Argt: V ':' TP {$$ = Envalloc(); $$->ID = yylval.nom; $$->type = renvoie_type_avec_un_noeud($3);}
    ;
TP: T_boo {$$ = Nalloc(); $$->codop = T_boo;}
    | T_int {$$ = Nalloc(); $$->codop = T_int;}
    | T_ar TP {$$ = Nalloc(); $$->codop = T_ar; $$->FG = $2;}
    ;
L_vart: %empty {$$ = bilenv_vide();}
    | L_vartnn {$$ = $1;}
    ;
L_vartnn: Var Argt {$$ = creer_bilenv($2);}
    | L_vartnn ',' Var Argt {$$ = concat($1, creer_bilenv($4));}
    ;
D_entp: Dep NPro '(' L_argt ')' {$$ = Lfonalloc(); $$->ID = yylval.nom; $$->PARAM = $4;}
    ;
D_entf: Def NFon '(' L_argt ')' ':' TP {$$ = Lfonalloc(); $$->ID = yylval.nom; ENV e = Envalloc(); e->ID = NULL; e->type = renvoie_type_avec_un_noeud($7); $$->PARAM = concat(creer_bilenv(e), $4);}
    ;
D: D_entp L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3;}
    | D_entf L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3;}
    ;
LD: %empty {$$ = bilfon_vide();}
    | LD D {$$ = concatfn($1, creer_bilfon($2));}
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
