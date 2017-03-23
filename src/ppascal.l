
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ppascal.tab.h"
%}


%%
[0-9]|[1-9][0-9]+ {/*yylval.val = atoi(yytext); return Nombre;*/}
:= {return Af;}
skip {return Sk;}
\; {return Se;}
if {return If;}
then {return Th;}
else {return El;} 
while {return Wh;}
do  {return Do;}
\+ {return Pl;}
- {return Mo;}
\* {return Mu;}
[A-Za-z]+|[A-Za-z]+[0-9]+ { /*
    yylval.nom = strdup(yytext);
    return Variable;
*/}
\) {return ')';}
\( {return '(';} 
\n {;}
%%
