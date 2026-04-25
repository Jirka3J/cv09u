#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Knihdbcd.h"

/* Databaze hudebnich alb - zadani */



int main()
{

    t_zaznamy databaze={0}; //databaze zaznamu
    int AktualniPozice=0; // aktuální pozice zobrazené položky k vylistovani
    int PocetPolozek=0;   //
    setlocale(LC_ALL,""); //umoznuje zobrazovat diakritiku

    loadDB(databaze,&PocetPolozek);
    t_akce vb=0;
    printf("                                DATABAZE HUDEBNICH ALB\n");
    printf("                                -----------\n");
    printf ("------------------------------------------------------------------------------\n");
    printf ("V databazi je aktualne %d polozek\n",PocetPolozek);
    TiskVyber();
    do
    {
    switch (vb=vyber())
    {
     case doleva:
         if ((AktualniPozice>0)&&(PocetPolozek>0))
                {
                system ("cls");
                TiskHlavicka();
                --AktualniPozice;
                VypisPolozku(AktualniPozice);
                TiskVyber();
                }
         break;
     case pridat:
            system ("cls");
            TiskHlavicka();
            MenuPridejPolozku(databaze,AktualniPozice,&PocetPolozek);
            system ("cls");
            TiskHlavicka();
            VypisPolozku(AktualniPozice);
            TiskVyber();
            break;
     case doprava:
          if ((AktualniPozice<(PocetPolozek-1))&&(PocetPolozek>0))
            {
            system ("cls");
            TiskHlavicka();
            ++AktualniPozice;
            VypisPolozku(AktualniPozice);
            TiskVyber();
            }
        break;
    }
    //system ("cls");
    }
    while (vb!=odejit);
    saveDB(databaze,&PocetPolozek);
    SmazDB(databaze,&PocetPolozek);
    return 0;
}
