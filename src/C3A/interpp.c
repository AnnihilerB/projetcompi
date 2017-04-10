#include <stdio.h>
#include "envGlobal.h"
#include "ppascal.tab.h"

extern void interpreteur(EnvGlobal env);
extern void execute_bison(); //dans ppascal.y
int main()
{
    execute_bison();
    interpreteur(envGlobal);
}
