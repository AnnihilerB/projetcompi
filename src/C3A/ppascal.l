
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "analyseur.h"
    #include "util.h"
    #include "ppascal.tab.h"
    enum {declareVariable, declareFonction, declareProcedure};
    int declare = declareVariable;
    int nbLigne = 1;
%}

%%
-[0-9]|-[1-9][0-9]+|[0-9]|[1-9][0-9]+ {
yylval.nom[1] = Idalloc();
strcpy(yylval.nom[1],yytext);
return I;
}

:= {return Af;}
= {return Eq;}
skip {return Sk;}
; {return Se;}
if {return If;}
then {return Th;}
else {return El;}
while {return Wh;}
do  {return Do;}
and {return And;}
or {return Or;}
\< {return Lt;}
\+ {return Pl;}
- {return Mo;}
\* {return Mu;}
\[ {;return '[';}
\] {return ']';}
\{ {return '{';}
\} {return '}';}

\) {return ')';}
\( {return '(';}
\n {nbLigne ++;}

true {return true;}
false {return false;}
var {return Var;}
defun {declare = declareFonction;return Def;}
defpro {declare = declareProcedure;return Dep;}
new {return NewAr;}
not {return Not;}
: {return yytext[0];}

integer {return T_int;}
boolean {return T_boo;}
array" "of {return T_ar;}
, {return yytext[0];}

[A-Za-z]+|[A-Za-z]+[0-9]+ {
    NOE v = Nalloc(); 
    v->ETIQ = Idalloc();
    strcpy(v->ETIQ,yytext); 
    yylval.noe = v;

    if (declare == declareVariable)
    {
        v->codop = V;
        yylval.noe = v;
        return V;
    }
    else if (declare == declareFonction)
    {
        v->codop = NFon;
        yylval.noe = v;
        declare = declareVariable;
        return NFon;
    }
    else if (declare == declareProcedure)
    {
        v->codop = NPro;
        yylval.noe = v;
        declare = declareVariable;
        declare = declareVariable;
        return NPro;
    }
}

%%

void afficherLigne()
{
    fprintf(stderr, "ligne : %d\n", nbLigne);
}
