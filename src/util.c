#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "environ.h"

NOE Nalloc()
{
    
}
LFON  Lfonalloc()
{
    
}
void prefix(NOE n){}
ENV creer_env(char *etiq, int val){}
ENV copier_env(ENV  env){}
char *nomop(int codop){}
ENV rech2(char *chaine, ENV rho_gb, ENV rho_lc){}
void inbilenv(BILENV *prho,char *var){}
BILENV bilenv_vide(){}
BILENV creer_bilenv(ENV var){}
BILENV copier_bilenv(BILENV b){}
BILENV concat(BILENV b1, BILENV b2){}
void ecrire_bilenv(BILENV b){}
void affectb(BILENV rho_gb, BILENV rho_lc, char *lhs, int rhs){}
LFON copier_fon(LFON lfn){}
void ecrire_fon(LFON bfn){}
LFON rechfon(char *chaine, LFON listident){}
BILFON bilfon_vide()
{
    BILFON b;
    b.debut = b.fin = NULL;
    return b;    
}
BILFON creer_bilfon(LFON pfon)
{
    BILFON b = bilfon_vide();
    b.debut = pfon;
    LFON w = b.debut;
    if (w != NULL)
    {
        while (w->SUIV != NULL)
        {
            w = w->SUIV;
        }
    }
    b.fin = w;
    return b;
}
BILFON copier_bilfon(BILFON bfn)
{
    BILFON b = bilfon_vide();
    if (bfn.debut != NULL)
    {
        b = creer_bilfon(copier_fon(b.debut));
    }
    return b;
    
}
BILFON concatfn(BILFON bfn1, BILFON bfn2)
{
    BILFON b = bilfon_vide();
    if (bfn1.debut != NULL && bfn2.debut != NULL)
    {
        b.debut = bfn1.debut;
        bfn1.fin->SUIV = bfn2.debut;
        b.fin = bfn2.fin;
    }
    else if (bfn2.debut != NULL)
    {
        b.debut = bfn2.debut;
        b.fin = bfn2.fin;
    }
    else if (bfn1.debut != NULL)
    {
        b = bfn1;
    }
    return b;
}
BILENV allvars(BILFON bfon)
{
    BILENV params = bilenv_vide();
    BILENV varloc = bilenv_vide();
    if (bfon.debut != NULL)
    {
        LFON w = bfon.debut;
        while (w != NULL)
        {
            params = concat(params, w->PARAM);
            varloc = concat(varloc, w->VARLOC);
            w = w->SUIV;
        }
    }
    return concat(params, varloc);
}
void ecrire_bilfon(BILFON bfn)
{
    LFON w = bfn.debut;
    if (w == NULL)
        printf("vide");
    else
    {        
        while(w != NULL)
        {
            printf("ID: %s ( ", w->ID);
            ecrire_bilenv(w->PARAM);
            printf(" )\n variables locales: \n");
            ecrire_bilenv(w->VARLOC);
            printf("\n");
            prefix(w->CORPS);
            w = w->SUIV;
        }
    }
    printf("\n");
}
void ecrire_prog(BILENV argb,BILFON argbf,NOE argno)
{
    printf("argb: \n");
    ecrire_bilenv(argb);
    printf("argbf: \n");
    ecrire_bilfon(argbf);
    printf("argno: \n");
    prefix(argno);
}
int main(int argc, char** argv)
{   
    BILFON b = bilfon_vide();
    printf("bilfon_vide: doit etre vide: ");
    ecrire_bilfon(b);
    LFON lfon = malloc(sizeof(struct cellfon));
    lfon->ID = "test 1";
    LFON lfon2 = malloc(sizeof(struct cellfon));
    lfon2->ID = "test 2";
    LFON lfon3 = malloc(sizeof(struct cellfon));
    lfon3->ID = "test 3";
    lfon->SUIV = lfon2->SUIV = lfon3->SUIV = NULL;
    
    printf("creer_bilfon: doit avoir un élement (test 1): \n");
    b = creer_bilfon(lfon);
    ecrire_bilfon(b);
    lfon->SUIV = lfon2;
    printf("creer_bilfon: doit avoir 2 élement (test 1 -> test 2): \n");
    b = creer_bilfon(lfon);
    ecrire_bilfon(b);
    
    printf("copier_bilfon: (en attente de copier_fon ");
    BILFON b2 = copier_bilfon(b);
    ecrire_bilfon(b2);
    printf("debut: %p == %p  et fin: %p == %p\n", b.debut, b2.debut, b.fin, b2.fin);
    
    b2 = creer_bilfon(lfon3);
    printf("concatfn:  doit avoir 3 élements (test1->test2->test3): \n");
    b = concatfn(b,b2);
    ecrire_bilfon(b);
}