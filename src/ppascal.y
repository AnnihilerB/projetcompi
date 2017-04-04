%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "analyseur.h"
    #include "util.h"
    int yyerror(char* s);
    int yylex();
    BILENV ListeVariables;
    BILFON ListeFonctionsGLOBALES;
    BILFON ListeFonctionsLOCALES;
    enum erreurs {NON_DEFINIE = 1, MAUVAIS_TYPE, MAUVAIS_TYPE_RETOUR, TYPES_DIFFERENT};

    void renvoyer_erreur(char* nom, int erreur);
    int verification_type_et_existence(char* nom1, char* nom2,ENV env1, ENV env2);
    extern  void setEnv(EnvGlobal env);
%}

%union{
        EnvGlobal envG;
        BILFON fonctionOuProcedure;
        BILENV varG;
        LFON fon;
        ENV env;
        NOE noe;
        char* nom[2]; //yylval.nom[0] -> variable, yylval.nom[1] -> entier
}
%start MP
%token T_boo T_int Def Dep Af true false Se If Th El Var Wh Do Pl Mo Mu And Or Not Lt Eq Sk NFon NPro NewAr I V T_ar

%type <fonctionOuProcedure> LD
%type <envG> MP
%type <varG> L_argt L_argtnn L_vart L_vartnn
%type <noe> C E Et Ca L_args L_argsnn TP V
%type <env> Argt
%type <fon> D_entp D_entf D
%left Se
%left Pl Mo Mu And Or Not Lt Eq

%%
//TODO: vérification de type
MP: L_vart LD C  {  printf("t_int : %d t_boo : %d et t_ar: %d\n",T_int, T_boo, T_ar);
                    $$=creer_environnementGlobal();
                    $$->variablesGlobales = $1;
                    $$->listeDesFonctionsOuProcedure = $2;
                    $$->corpsGlobale = $3;
                    //interpreteur($$);
                    ecrire_prog($$->variablesGlobales, $$->listeDesFonctionsOuProcedure, $$->corpsGlobale);
                }
    ;
E: E Pl E   {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "addition possible seulement entre integer\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = Pl; $$->FD =  $3;
            }
            
    | E Mo E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "soustraction possible seulement entre integer\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = Mo; $$->FD =  $3;
             }
             
    | E Mu E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "multiplication possible seulement entre integer\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = Mu; $$->FD =  $3;
             }
             
    | E Or E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_boo && env2->type.type != T_boo)
                {
                    fprintf(stderr, "ou possible seulement entre boolean\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = Or; $$->FD =  $3;
             }
             
    | E Lt E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_int && env2->type.type != T_int)
                {
                    fprintf(stderr, "comparaison possible seulement entre integer\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = Lt; $$->FD =  $3;
             }        
    | E Eq E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                $$ = Nalloc(); $$->FG = $1; $$->codop = Eq; $$->FD =  $3;
             }        
    | E And E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariables);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariables);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                if (env1->type.type != T_boo && env2->type.type != T_boo)
                {
                    fprintf(stderr, "and possible seulement entre boolean\n");
                    return 1;
                }
                $$ = Nalloc(); $$->FG = $1; $$->codop = And; $$->FD =  $3;
              }      
    | Not E {
                Env env = existe($2, ListeFonctionsGLOBALES, ListeVariables);
                if (env == NULL)
                {
                    renvoyer_erreur($2->ETIQ, NON_DEFINIE);
                    return 1;
                }
                else if (env->type.type != T_boo)
                {
                    fprintf(stderr, "not possible seulement avec un boolean\n");
                    return 1;
                }
                $$ = Nalloc(); $$->codop = Not; $$->FD = $2;
            }
    | '(' E ')' {
                    Env env = existe($2, ListeFonctionsGLOBALES, ListeVariables);
                    
                    $$ = $2;
                }
    | I {$$ = Nalloc(); $$->codop = I; $$->ETIQ = yylval.nom[1];}
    | V {$$ = $1;}
    | true {$$ = Nalloc(); $$->codop = true;}
    | false {$$ = Nalloc(); $$->codop = false;}
    | V '(' L_args ')' { $$ = $1; $$->FG = $3; $$->FD = NULL;}
    | NewAr TP '[' E ']' {$$ = Nalloc(); $$->codop = NewAr; $$->FG = $2; $$->FD = $4;}
    | Et {$$ = $1;}
    ;
Et: V '[' E ']' {NOE v = Nalloc(); v->codop = V; v->ETIQ = $1->ETIQ; $$ = Nalloc(); $$->codop = V; $$->ETIQ = v->ETIQ; $$->FG = $1; $$->FD = $3; }
    | Et '[' E ']' {$$ = Nalloc() ;$$->FG = $1; $$->FD = $3; $$->ETIQ = $1->ETIQ;}
    ;
C: C Se C {$$ = Nalloc(); $$->FG = $1; $$->codop = Se; $$->FD = $3;}
    | Sk {$$ = Nalloc(); $$->codop = Sk;}
    | '{' C '}' {$$ = $2;}
    | V '(' L_args ')' { $$ = $1; $$->FG = $3; $$->FD = NULL;}
    | Ca {$$ = $1;}
    ;

Ca: Wh E Do Ca {$$ = Nalloc(); $$->codop = Wh; $$->FG = $2; $$->FD = $4;}
  | If E Th C El Ca {$$ = Nalloc(); $$->codop = If; $$->FG = $2; NOE noeVide = Nalloc(); noeVide->FG = $4; noeVide->FD = $6; $$->FD = noeVide;}
  | Et Af E {$$ = Nalloc(); $$->codop = Af; $$->FG = $1; $$->FD = $3;}
  | V Af E {$$ = Nalloc(); $$->codop = Af; $$->FG = $1; $$->FD = $3; }
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
    | L_argtnn ',' Argt {$$ = concat($1, creer_bilenv($3)); }
    ;
Argt: V ':' TP {$$ = Envalloc(); $$->ID = $1->ETIQ; $$->type = renvoie_type_avec_un_noeud($3);}
    ;
TP: T_boo {$$ = Nalloc(); $$->codop = T_boo;}
    | T_int {$$ = Nalloc(); $$->codop = T_int;}
    | T_ar TP {$$ = Nalloc(); $$->codop = T_ar; $$->FG = $2;}
    ;
L_vart: %empty {$$ = bilenv_vide();}
    | L_vartnn {$$ = $1; ListeVariables = $$;}
    ;
L_vartnn: Var Argt {$$ = creer_bilenv($2);}
    | L_vartnn ',' Var Argt {$$ = concat($1, creer_bilenv($4)); }
    ;
D_entp: Dep NPro '(' L_argt ')' {$$ = Lfonalloc(); $$->ID = yylval.nom[0]; $$->PARAM = $4;}
    ;
D_entf: Def NFon '(' L_argt ')' ':' TP {$$ = Lfonalloc(); $$->ID = yylval.nom[0]; ENV e = Envalloc(); e->ID = NULL; e->type = renvoie_type_avec_un_noeud($7); $$->PARAM = concat(creer_bilenv(e), $4);}
    ;
D: D_entp L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3;}
    | D_entf L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3;}
    ;
LD: %empty {$$ = bilfon_vide();}
    | LD D {$$ = concatfn($1, creer_bilfon($2)); ListeFonctionsGLOBALES = $$;}
    ;


%%
BILENV retourner_variables_fonctions(LFON fonction)
{
    BILENV param = copier_bilenv(fonction->PARAM);
    BILENV varloc = copier_bilenv(fonction->VARLOC);
    return concat(param,varloc);
}
int verfication_existence (Env env)
{
    
}
int verification_type_et_existence(char* nom1, char* nom2,ENV env1, ENV env2)
{

    int retour = 1;
    if (env1 == NULL || env2 == NULL)
    {
        if (env1 == NULL)
            renvoyer_erreur(nom1, NON_DEFINIE);
        if (env2 == NULL)
            renvoyer_erreur(nom2, NON_DEFINIE);
    }
    else     //ils existent, maintenant on vérifie les types
    {
        if (env1->type.type == 0)   //procédure
            renvoyer_erreur(nom1, MAUVAIS_TYPE_RETOUR);
        else if (env2->type.type == 0)
            renvoyer_erreur(nom2, MAUVAIS_TYPE_RETOUR);
        else if (compare_type(env1->type, env2->type) != 1)
        {
            fprintf(stderr, "%s et %s n'ont pas les même type\n", nom1, nom2);
        }
        else
            retour = 0;
    }
    return retour;
}
void renvoyer_erreur(char* nom, int erreur)
{

    if (nom != NULL)        
        fprintf(stderr, "%s ", nom);
        
    if (erreur == NON_DEFINIE)
        fprintf(stderr, "non definie");
    else if (erreur == MAUVAIS_TYPE)
        fprintf(stderr, "est du mauvais type");
    else if (erreur == MAUVAIS_TYPE_RETOUR)
        fprintf(stderr, "le type de retour est mauvais");
        
    fprintf(stderr, "\n");
}
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
