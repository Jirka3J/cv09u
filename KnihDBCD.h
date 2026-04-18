#ifndef KNIHDBCD_H_INCLUDED
#define KNIHDBCD_H_INCLUDED

#define MAXDBSIZE 50


typedef enum  {nahoru,dolu,doprava,doleva,pridat,smazat,odejit,enter} t_akce; //výètový typ pro ovládání akcí rozhraní konzoly
typedef enum {jazz,klasika,pop,rock} t_zanry;//### výètový typ t_zanry

typedef struct{
   char skupina[50];
   t_zanry zanr;
   char album[50];
} t_album;

typedef  t_album* t_zaznamy[MAXDBSIZE];//### ......  definice datoveho typu t_zaznamy;

t_akce vyber();
void VypisPolozku (t_album *pol, int pozice);
void MenuPridejPolozku (t_zaznamy databaze, int pozice, int *recnum);
void SmazDB (t_zaznamy databaze, int *recnum);
void TiskVyber();
void TiskHlavicka();
int loadDB(t_zaznamy databaze,int *pocet);
int saveDB(t_zaznamy databaze,int *pocet);
#endif // KNIHDBCD_H_INCLUDED
