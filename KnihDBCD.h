#ifndef KNIHDBCD_H_INCLUDED
#define KNIHDBCD_H_INCLUDED

typedef enum  {nahoru,dolu,doprava,doleva,pridat,smazat,odejit,enter} t_akce; //výètový typ pro ovládání akcí rozhraní konzoly
typedef enum {jazz,klasika,pop,rock} t_zanry;//### výètový typ t_zanry

typedef struct{
   char skupina[50];
   t_zanry zanr;
   char album[];
} t_album;

typedef  t_album* t_zaznamy[50];//### ......  definice datoveho typu t_zaznamy;

t_akce vyber();
void VypisPolozku (t_album *pol);
void MenuPridejPolozku (t_zaznamy databaze, int pozice, int *recnum);
void SmazDB (t_zaznamy databaze, int *recnum);
void TiskVyber();
void TiskHlavicka();
#endif // KNIHDBCD_H_INCLUDED
