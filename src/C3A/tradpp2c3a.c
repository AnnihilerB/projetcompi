#include "envGlobal.h"
#include "traducteurC3A.h"
#include "bilquad.h"
#include "ppascal.tab.h"

extern int execute_bison(); //dans ppascal.y

int main()
{
    if (execute_bison() == 1)
        return 1;
    BILQUAD b = traduire_ppascal_vers_C3A(envGlobal);
    ecrire_bilquad(b);
}
