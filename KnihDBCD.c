#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Knihdbcd.h"

t_album* PridejPolozku (char *kapela, char *album, t_zanry zanr);

t_album* listStart=NULL;
t_album* last;
t_album* actual;




int loadDB(t_zaznamy databaze,int *pocet) {
    FILE *f = NULL;
    f = fopen("DB.txt","r");
    t_album buffer;
    do {
        fscanf(f,"%[^|] |%d |%[^\n]\n",buffer.skupina,&buffer.zanr,buffer.album);
        actual=PridejPolozku(buffer.skupina,buffer.album,buffer.zanr);
        if(listStart==NULL) {
            listStart=actual;
            last=actual;
        }else {

            last->nextptr=actual;
        }
        last=actual;
        *pocet+=1;
    }while(!feof(f)&&(*pocet<=MAXDBSIZE));
    fclose(f);
    return 0;
}
int saveDB(t_zaznamy DB,int *pocet) {
    FILE *f = fopen("DB.txt","w");
    actual=listStart;
    for(int i=0; i<*pocet;i++) {
        fprintf(f,"%s |%d |%s\n",actual->skupina,actual->zanr,actual->album);
        actual=actual->nextptr;
    }
    fclose(f);
    return 0;
}

t_akce vyber() //vraci enumerativni typ moznosti klaves vyberu akci

{
int ch1=0, ch2 =0;
fflush(stdin);
ch1 = getch();
ch2 = 0;
if (ch1 == 0xE0)
    {
    ch2 = getch();

        // determine what it was
        switch(ch2)
        {
        case 72: return nahoru;//sipka nahoru
        case 80: return dolu;//sipka dolu
        case 75: return doleva;//sipka doleva
        case 77: return doprava;//sipka doprava
        // zde je mozne pridat dalsi varianty specialnich znaku, PgUp, PgDn, End atd...
        };

    }
else
    {
        switch (ch1)
        {
        case 'a': return pridat;
        case 'q': return odejit;
        case 13: return enter;
        }
    }
    fflush(stdin);
}

void VypisPolozku (int pozice)
{
    t_album* zobr=listStart;
    for(int i=0;i<pozice;i++){zobr=zobr->nextptr;}
    printf ("\n AKTUALNI POLOZKA: %d\n",pozice+1);
    printf (" Skupina: %s\n",zobr->skupina);
    printf (" Album: %s\n",zobr->album);
    switch (zobr->zanr){
        case jazz: printf (" Zanr: jazz\n" ); break;
        case pop: printf (" Zanr: pop\n" ); break;
        case klasika: printf (" Zanr: klasika\n" ); break;
        case rock: printf (" Zanr: rock\n" ); break;
    }
}



t_album* PridejPolozku (char *kapela, char *album, t_zanry zanr)  //vraci ukazatel na novou polozku
{
    t_album *ptr;
    ptr=(t_album*)malloc(sizeof(t_album));
    strcpy(ptr->skupina,kapela);
    strcpy(ptr->album,album);
    ptr->zanr=zanr;
    ptr->nextptr=NULL;
    return ptr;
}


void MenuPridejPolozku (t_zaznamy databaze, int pozice, int *recnum) //pozice za aktualni polozkou, tzn. kam se ma pridat zaznam
{
    char nazev[50],album[50];
    int key=0;
    t_zanry zanr=1;
    printf ("------------------------------------------------------------------------------\n");
    printf ("\t\t\tVKLADANI NOVE POLOZKY \n");
    printf ("\t\t\tNazev kapely:");
    fflush(stdin);
    gets (nazev);
    printf ("\t\t\tZadej nazev alba:");
    fflush(stdin);
    gets (album);
    fflush(stdin);
    printf ("\t\t\tsipkami vyber zanr:");
    printf ("   jazz");
    zanr = jazz;
   do
    {
        key=vyber();
        if ((key==nahoru)&&(zanr>jazz)) zanr--;
        if ((key==dolu)&&(zanr<rock)) zanr++;
         switch (zanr)
        {
        case jazz: printf ("\b\b\b\b\b\b\b   jazz"); break;
        case pop: printf ("\b\b\b\b\b\b\b    pop"); break;
        case klasika:printf ("\b\b\b\b\b\b\bklasika"); break;
        case rock:printf ("\b\b\b\b\b\b\b   rock"); break;
        }
    }
    while (key!=enter);




    // VARIANTA vlozit zaznam do prazdne databaze//
 if (((*recnum)==0)){
     listStart=PridejPolozku(nazev,album,zanr);
     *recnum +=1;
     // VARIANTA vlozit zaznam na konec databaze //
 }else if((pozice+1)==(*recnum)) {
     t_album* last=listStart;
     t_album* actual=last->nextptr;
     do{
         last=actual;
         actual=last->nextptr;
     }while(actual!=NULL);
     actual->nextptr=PridejPolozku(nazev,album,zanr);
 }

 else  //pridavam doprostred pole
 {
     pozice++;
     actual=listStart;
     do {
         last=actual;
         actual=last->nextptr;
         pozice--;
     }while(pozice!=0);
     last->nextptr=PridejPolozku(nazev,album,zanr);
     (last->nextptr)->nextptr=actual;
     *recnum +=1;
 }


}

void SmazDB (t_zaznamy databaze, int *recnum)
{
    if ((*recnum) > 0){
        actual=listStart;
        do{
            actual=actual->nextptr;
            free(actual);
        }while (actual->nextptr!=NULL);
    }
}

void TiskVyber()
{
printf ("------------------------------------------------------------------------------\n");
    printf ("Vyber: sipkami vlevo a vpravo prohlizej zaznamy \n");
    printf ("[a]  Pridej zaznam za aktualni polozku\n");
    printf ("[q]  Ukonci program\n");
}
void TiskHlavicka()
{
    printf("                                DATABAZE HUDEBNICH ALB\n");
    printf("                                -----------\n");
    printf ("------------------------------------------------------------------------------\n");
}
