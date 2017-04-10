#include <stdio.h>
#include "envGlobal.h"
#include "ppascal.tab.h"


int main()
{
    execute_bison();
    interpreteur(envGlobal);
}
