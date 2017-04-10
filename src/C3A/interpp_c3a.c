#include "envGlobal.h"
#include "traducteurC3A.h"
#include "ppascal.tab.h"


int main()
{
    execute_bison();
    BILQUAD b = traduire_ppascal_vers_C3A(envGlobal);
    interpreteurC3A(b);
}
