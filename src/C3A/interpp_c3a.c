#include "envGlobal.h"
#include "traducteurC3A.h"
#include "ppascal.tab.h"

extern execute_bison(); //dans ppascal.y
int main()
{
    execute_bison();
    BILQUAD b = traduire_ppascal_vers_C3A(envGlobal);
    interpreteurC3A(b);
}
