%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "analyseur.h"
    #include "util.h"
    int yyerror(char* s);
    int yylex();
    BILENV ListeVariablesGLOBALES;
    BILFON ListeFonctionsGLOBALES;
    BILENV ListeVariablesLOCALES;
    char* fonctionActuel;       //dans quelle fonction se passe le code
    enum erreurs {NON_DEFINIE = 1, MAUVAIS_TYPE, MAUVAIS_TYPE_RETOUR, TYPES_DIFFERENT};
    int estDansFonction;

    void renvoyer_erreur(char* nom, int erreur);
    int verification_type_et_existence(char* nom1, char* nom2,ENV env1, ENV env2);
    int verification_appel_fonction (LFON fonction, NOE args);
    int numeroLigne = 0;
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
%type <noe> C E Et Ca L_args L_argsnn TP V NPro NFon
%type <env> Argt
%type <fon> D_entp D_entf D
%left Se
%left Pl Mo Mu And Or Not Lt Eq

%%
//TODO: vérification de type
MP: L_vart LD C  {  printf("t_int : %d t_boo : %d et t_ar: %d et Nfon: %d\n",T_int, T_boo, T_ar, NFon);
                    $$=creer_environnementGlobal();
                    $$.variablesGlobales = $1;
                    $$.listeDesFonctionsOuProcedure = $2;
                    $$.corpsGlobale = $3;
                    printf("INTERP\n");
                    interpreteur($$);
                    ecrire_prog($$.variablesGlobales, $$.listeDesFonctionsOuProcedure, $$.corpsGlobale);
                }
    ;
E: E Pl E   {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
                $$ = Nalloc(); $$->FG = $1; $$->codop = Eq; $$->FD =  $3;
             }        
    | E And E { 
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
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
                ENV env = existe($2, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (env == NULL)
                {
                    renvoyer_erreur($2->ETIQ, NON_DEFINIE);
                    return 1;
                }
                if (env->type.type != T_boo)
                {
                    fprintf(stderr, "not possible seulement avec un boolean\n");
                    return 1;
                }
                $$ = Nalloc(); $$->codop = Not; $$->FD = $2;
            }
    | '(' E ')' {
                    ENV env = existe($2, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                    if (env == NULL)
                    {
                        renvoyer_erreur($2->ETIQ, NON_DEFINIE);
                        return 1;
                    }                    
                    $$ = $2;
                }
    | I {$$ = Nalloc(); $$->codop = I; $$->ETIQ = yylval.nom[1];}
    | V {
            ENV env = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            if (env == NULL)
            {
                renvoyer_erreur($1->ETIQ, NON_DEFINIE);
                return 1;
            }
            $$ = $1;
        }
    | true {$$ = Nalloc(); $$->codop = T_boo; $$->ETIQ = "true";}
    | false {$$ = Nalloc(); $$->codop = T_boo; $$->ETIQ = "false";}
    | V '(' L_args ')' {
                            LFON fonction = rechercher_lfon($1->ETIQ,ListeFonctionsGLOBALES.debut);
                            if (fonction == NULL)
                            {
                                renvoyer_erreur($1->ETIQ, NON_DEFINIE);
                                return 1;
                            }
                            if (verification_appel_fonction(fonction, $3) != 0)
                                return 1;
                            $$ = Nalloc(); $$->codop = NFon; $$->ETIQ = $1->ETIQ; $$->FG = $3; $$->FD = NULL;
                            
                       }
    | NewAr TP '[' E ']' {
                            ENV env = existe($4, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                            if (env == NULL)
                            {
                                renvoyer_erreur($4->ETIQ, NON_DEFINIE);
                                return 1;
                            }
                            if (env->type.type != T_int)
                            {
                                fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                                return 1;
                            }
                            $$ = Nalloc(); $$->codop = NewAr; $$->FG = $2; $$->FD = $4;
                         }
    | Et {$$ = $1;}
    ;
Et: V '[' E ']' {   
                    ENV env = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                    if (env == NULL)
                    {
                        renvoyer_erreur($3->ETIQ, NON_DEFINIE);
                        return 1;
                    }
                    if (env->type.type != T_int)
                    {
                        fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                        return 1;
                    }
                    NOE v = Nalloc(); v->codop = V; v->ETIQ = $1->ETIQ; $$ = Nalloc(); $$->codop = V; $$->ETIQ = v->ETIQ; $$->FG = $1; $$->FD = $3; 
                }
    | Et '[' E ']' {
                        ENV env = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                        if (env == NULL)
                        {
                            renvoyer_erreur($3->ETIQ, NON_DEFINIE);
                            return 1;
                        }
                        if (env->type.type != T_int)
                        {
                            fprintf(stderr,"l'indice ou la taille d'un tableau doit être un int\n");
                            return 1;
                        }
                            $$ = Nalloc() ;$$->FG = $1; $$->FD = $3; $$->ETIQ = $1->ETIQ;
                    }
    ;
C: C Se C {$$ = Nalloc(); $$->FG = $1; $$->codop = Se; $$->FD = $3;}
    | Sk {$$ = Nalloc(); $$->codop = Sk;}
    | '{' C '}' {$$ = $2;}
    | V '(' L_args ')'  {
                            LFON fonction = rechercher_lfon($1->ETIQ,ListeFonctionsGLOBALES.debut);
                            if (fonction == NULL)
                            {
                                renvoyer_erreur($1->ETIQ, NON_DEFINIE);
                                return 1;
                            }
                            if (verification_appel_fonction(fonction, $3) != 0)
                                return 1;
                            $$ = Nalloc(); $$->codop = NFon; $$->ETIQ = $1->ETIQ; $$->FG = $3; $$->FD = NULL;
    
                        }
    | Ca {$$ = $1;}
    ;

Ca: Wh E Do Ca {
                ENV env = existe($2, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (env == NULL)
                {
                    renvoyer_erreur($2->ETIQ, NON_DEFINIE);
                    return 1;
                }
                if (env->type.type != T_boo)
                {
                    fprintf(stderr, "la condition de la boucle while n'est pas un boolean\n");
                    return 1;
                }
                $$ = Nalloc(); $$->codop = Wh; $$->FG = $2; $$->FD = $4;
              }
  | '{' C '}' {$$ = $2;}
  | Sk {$$ = Nalloc(); $$->codop = Sk;}
  | If E Th C El Ca {
                        ENV env = existe($2, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                        if (env == NULL)
                        {
                            renvoyer_erreur($2->ETIQ, NON_DEFINIE);
                            return 1;
                        }
                        if (env->type.type != T_boo)
                        {
                            fprintf(stderr, "la condition du if n'est pas un boolean\n");
                            return 1;
                        }
                        $$ = Nalloc(); $$->codop = If; $$->FG = $2; NOE noeVide = Nalloc(); noeVide->FG = $4; noeVide->FD = $6; $$->FD = noeVide;
                    }
  | Et Af E {
                ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
                if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                {
                    printf("test: ");
                    ecrire_type(env1->type);
                    ecrire_type(env2->type);
                    return 1;
                }
                $$ = Nalloc(); $$->codop = Af; $$->FG = $1; $$->FD = $3;
            }
  | V Af E {
            ENV env1 = existe($1, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            ENV env2 = existe($3, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
            if (fonctionActuel != NULL)
            {
                if (strcmp($1->ETIQ, fonctionActuel) != 0)
                {
                    if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                        return 1;
                }
                else
                {
                    //comme on est dans le return, on vérifie qu'on retourne bien le bon type
                    LFON fonction = rechercher_lfon(fonctionActuel, ListeFonctionsGLOBALES.debut);
                    Type t = renvoie_type_fonction(fonction);
                    if (t.type == 0)    //procédure
                    {
                        fprintf(stderr, "%s est un procedure, n'a donc pas de valeur de retour", fonctionActuel);
                        return 1;
                    }
                    else if (env2 == NULL)
                    {
                        renvoyer_erreur($3->ETIQ, NON_DEFINIE);
                        return 1;
                    }
                    else if (compare_type(t, env2->type) != 1)
                    {
                        fprintf(stderr, "la fonction %s ne renvoie pas le bon type\n", fonctionActuel, env2->ID);
                        return 1;
                    }
                }
            }
            else if (verification_type_et_existence($1->ETIQ,$3->ETIQ,env1, env2) != 0)
                    return 1;
            
            $$ = Nalloc(); $$->codop = Af; $$->FG = $1; $$->FD = $3; 
           }
  ;
L_args: %empty {$$ = NULL;}
    | L_argsnn {$$ = $1;}
    ;
L_argsnn: E {$$ = Nalloc(); $$->FD = $1; }
    | E ',' L_argsnn {$$ = Nalloc(); $$->FD = $1; $$->FG = $3;}
    ;
L_argt: %empty {$$ = bilenv_vide();}
    | L_argtnn {$$ = $1;}
    ;
L_argtnn: Argt {$$ = creer_bilenv($1);}
    | L_argtnn ',' Argt {$$ = concat($1, creer_bilenv($3)); }
    ;
Argt: V ':' TP {$$ = Envalloc(); $$->ID = $1->ETIQ; $$->type = renvoie_type_avec_un_noeudVariable($3);}
    ;
TP: T_boo {$$ = Nalloc(); $$->codop = T_boo;}
    | T_int {$$ = Nalloc(); $$->codop = T_int;}
    | T_ar TP {$$ = Nalloc(); $$->codop = T_ar; $$->FG = $2;}
    ;
L_vart: %empty {$$ = bilenv_vide();}
    | L_vartnn {    $$ = $1; 
                    if (estDansFonction == false)
                        ListeVariablesGLOBALES = $$;
                    else
                        concat(ListeVariablesLOCALES, copier_bilenv($$));
               }
    ;
L_vartnn: Var Argt {$$ = creer_bilenv($2);}
    | L_vartnn ',' Var Argt {$$ = concat($1, creer_bilenv($4)); }
    ;
D_entp: Dep NPro '(' L_argt ')' {$$ = Lfonalloc(); $$->ID = $2->ETIQ; $$->PARAM = $4; ListeVariablesLOCALES = copier_bilenv($4); estDansFonction = true; ListeFonctionsGLOBALES = concatfn(ListeFonctionsGLOBALES, creer_bilfon($$)); fonctionActuel = $$->ID;}
    ;
D_entf: Def NFon '(' L_argt ')' ':' TP {$$ = Lfonalloc(); $$->ID = $2->ETIQ; ENV e = Envalloc(); e->ID = NULL; e->type = renvoie_type_avec_un_noeudVariable($7); $$->PARAM = concat(creer_bilenv(e), $4); ListeVariablesLOCALES = copier_bilenv($4); estDansFonction = true; ListeFonctionsGLOBALES = concatfn(ListeFonctionsGLOBALES, creer_bilfon($$)); fonctionActuel = $$->ID;}
    ;
D: D_entp L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3;estDansFonction = false; ListeVariablesLOCALES = bilenv_vide(); fonctionActuel = NULL;}
    | D_entf L_vart C {$$ = Lfonalloc(); $$->ID = $1->ID; $$->PARAM = $1->PARAM; $$->VARLOC = $2; $$->CORPS = $3; estDansFonction = false; ListeVariablesLOCALES = bilenv_vide(); fonctionActuel = NULL;}
    ;
LD: %empty {$$ = bilfon_vide();}
    | LD D {$$ = concatfn($1, creer_bilfon($2));}
    ;


%%
int verification_appel_fonction (LFON fonction, NOE args)
{
    if (fonction == NULL)
    {
        return -1;
    }
    int retour = 0;
    NOE noeudArg = args;
    ENV envFonction = fonction->PARAM.debut;
    if (envFonction != NULL && envFonction->ID == NULL)     //si c'est une fonction le premier arg est le type de retour
    {
        envFonction = envFonction->SUIV;
    }
    int erreur = 0;
    //ecrire_env(envFonction);
    int numArg = 1;
    while (noeudArg != NULL && envFonction != NULL)
    {
        ENV envNoeudArg = existe(noeudArg->FD, ListeFonctionsGLOBALES, ListeVariablesGLOBALES, ListeVariablesLOCALES);
        //ecrire_env(envNoeudArg);
        if (envNoeudArg == NULL)
        {   
            erreur = 2;
            retour = 1;
            break;
        }
        if (compare_type(envNoeudArg->type, envFonction->type) != 1)
        {
            fprintf(stderr, "l'argument %d n'est pas du bon type, dans l'appel de la fonction %s\n", numArg, fonction->ID);
            erreur = 1;
            retour = 1;
            break;
        }
        noeudArg = noeudArg->FG;
        envFonction = envFonction->SUIV;
        numArg ++;
    }
    if (erreur != 1)
    {
        if (noeudArg != NULL || envFonction != NULL)
        {
            fprintf(stderr, "l'appel de %s ne contient pas le bon nombre d'arguments\n", fonction->ID);
            retour = 1;
        }
        else if (erreur == 2)
        {
            if (noeudArg != NULL)
                renvoyer_erreur(noeudArg->FD->ETIQ, NON_DEFINIE);
                
        }
    }
    return retour;
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
    fonctionActuel = NULL;
    ListeVariablesLOCALES = bilenv_vide();
    ListeFonctionsGLOBALES = bilfon_vide();
    estDansFonction = false;
    if (yyparse() == 1)
        afficherLigne();
    return 0;
}
