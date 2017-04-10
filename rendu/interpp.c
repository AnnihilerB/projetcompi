#include <stdio.h>
#include "envGlobal.h"
#include "ppascal.tab.h"

extern void interpreteur(EnvGlobal env);
extern int execute_bison(); //dans ppascal.y
int main()
{
    if (execute_bison() == 1)
        return 1;
    interpreteur(envGlobal);
}
