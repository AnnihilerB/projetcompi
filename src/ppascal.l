
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ppascal.tab.h"
%}
%%
[0-9]|[1-9][0-9]+ {return I;}
:= {return Af;}
skip {return Sk;}
; {return Se;}
if {return If;}
then {return Th;}
else {return El;}
while {return Wh;}
do  {return Do;}
\+ {return Pl;}
- {return Mo;}
\* {return Mu;}


\) {return ')';}
\( {return '(';}
\n {;}

var {printf("var\n");return Var;}



: {return yytext[0];}

integer {printf("int\n");return T_int;}
boolean {printf("bool\n");return T_boo;}
array" "of {return T_ar;}
, {printf("virgule\n");return yytext[0];}


[A-Za-z]+|[A-Za-z]+[0-9]+ {
  printf("V\n");
    return V;
}

%%
