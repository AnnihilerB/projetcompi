
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "analyseur.h"
    #include "util.h"
    #include "ppascal.tab.h"
    enum {declareVariable, declareFonction, declareProcedure};
    int declare = declareVariable;
%}

%%
[0-9]|[1-9][0-9]+ {yylval.nom = strdup(yytext);return I;}
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
\n {;}

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
    yylval.nom = strdup(yytext);
    if (declare == declareVariable)
        return V;
    else if (declare == declareFonction)
    {
        declare = declareVariable;
        return NFon;
    }
    else if (declare == declareProcedure)
    {
        declare = declareVariable;
        return NPro;
    }
}

%%
