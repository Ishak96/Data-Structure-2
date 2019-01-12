#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include <math.h>

#define TMAX 100

typedef int TElement;

typedef struct 
{
	TElement entier;
	int nbOcc;
}nombre;

typedef struct Cellule{
	nombre nbr;
	struct Cellule *suivant;
}*liste;

typedef struct 
{
	int monNombre;
	liste l;
}facteurNombres;

typedef struct 
{
	int nbElem;
	int nbElemMax;
	facteurNombres *tab;
}TabList;

/*(1)premitive*/
int monNombre(facteurNombres fac){
	return fac.monNombre;
}

liste facteurNombresListe(facteurNombres fac){
	return fac.l;
}

facteurNombres IemeElemFacteur(int i, TabList Tab){
	return Tab.tab[i];
}

TElement entierNombre(nombre nbr){
	return nbr.entier;
}

int nbOccNombre(nombre nbr){
	return nbr.nbOcc;
}

nombre nombreCourant(liste l){
	return l->nbr;

}

liste suivCellule(liste l){
	return l->suivant;

}

TabList Allouer(int Nmax){

   TabList Tab ;

     Tab.nbElemMax=Nmax;

     Tab.nbElem=0;

     Tab.tab=(facteurNombres*)malloc(Nmax*sizeof(facteurNombres));

   return Tab;

}

/*(2)initialise une liste*/
liste initListe(){
	return NULL;

}

/*(3) teste si une liste est vide ou non*/
int videListe(liste l){

	return l == NULL;

}

/*(4) afficher les valeurs des differentes cellules de la liste*/
void affListe(liste l){
	while(!videListe(l))
	{
		printf("(%d,%d) ",entierNombre(nombreCourant(l)),nbOccNombre(nombreCourant(l)));
	
		l = suivCellule(l);
	}
	printf("\n");
}

/*5) ajouter un nombre en tete de la liste */
void inserTete(nombre nbr , liste *l){

  liste cel;
  //creation de la cellule
  cel = (liste) malloc (sizeof(struct Cellule));
  //remplissage de la cellule
  cel->nbr = nbr;
  //chainage 
  cel->suivant = *l;
  *l = cel;
}

/*6) determiner le dernier nombre d'une liste */
liste dernierNombre(liste l){
 if( !videListe(l) )
 {
   while( !videListe(l->suivant) )
   {
	l = suivCellule(l);
   }
 }
	return l;
}

/*7) ajouter un nombre en queue d'une liste */
void inserQueue(nombre nbr , liste *l){
  
  if( videListe(*l) )
	inserTete(nbr, l);
  else
  {
  	liste cel;
  	liste der;
  	der = dernierNombre(*l);
  	//creation de la cellule
  	cel = (liste) malloc (sizeof(struct Cellule));
  	//remplissage de la cellule 
  	cel->nbr = nbr;
  	//chainege
  	cel->suivant = NULL;
  	der->suivant = cel;
  }
}

/*8) determinner l'adresse de la liste precedent */
liste numeroPrecedent(nombre nbr , liste l){

    while( !videListe(l->suivant) && nbOccNombre(nbr) >= nbOccNombre(nombreCourant(l->suivant)) )
    {
		l = suivCellule(l);
    }
    return l;
}

/*9) determiner l'adresse du nombre s'il existe on fait la recherche par rapport aux nombre d'occurences */
liste appartienMonome(nombre nbr , liste l){
   while( (!videListe(l)) && (nbOccNombre(nbr) > nbOccNombre(nombreCourant(l))) ){
		l = suivCellule(l);
   }
  return l;
}

/*10) supprimer le nombre en tete de la liste */
void suppTete(liste *l){
  liste cel ;
  //conservation de la premiere cellule
  cel = *l;
  //chainage
  *l = suivCellule(*l);
  free(cel);
}

/*11) supprime un polynome */
void delListe(liste *l){
  while( !videListe(*l) )
  {
	suppTete(l);
  }
}

facteurNombres decompEntier(TElement nbr){
	liste l;
	int nbOcc,d,rn,num;
	facteurNombres fac;

	l=initListe();
	rn=nbr/2;
	d=2;
	nbOcc=0;
	num=nbr;

	while(nbr>1 && d<=rn)
	{
		if(nbr%d==0)
		{
			nbOcc=nbOcc+1;
			nbr=nbr/d;
		}
		else
		{
			if (nbOcc!=0)
			{
				nombre monNombre={d,nbOcc};
				inserQueue(monNombre,&l);
				nbOcc=0;
			}
			d=d+1;
		}
	}
	if (nbOcc!=0)
	{
		nombre monNombre={d,nbOcc};
		inserQueue(monNombre,&l);
	}
	
	if (videListe(l))
	{
		nombre monNombre={nbr,1};
		inserTete(monNombre,&l);
	}
	
	fac.monNombre=num;
	fac.l=l;

	return fac;
}

void remplissageTabList(TabList *Tab, TElement *tab, int n){
	facteurNombres fac;
	*Tab=Allouer(n);

	for (int i = 0; i < n; i++)
	{
		fac=decompEntier(tab[i]);
		Tab->tab[Tab->nbElem]=fac;
		Tab->nbElem=Tab->nbElem+1;
	}
}

void affTabList(TabList Tab){
	facteurNombres fac;
	for (int i = 0; i < Tab.nbElem; i++)
	{
		fac=Tab.tab[i];
		printf("%d|->", fac.monNombre);
		affListe(fac.l);
	}
	printf("\n");
}

int minNbOcc(int nbOcc1, int nbOcc2){
	int min;

	min=nbOcc1;
	if (nbOcc1>nbOcc2)
	{
		min=nbOcc2;
	}

	return min;
}

void intersecListe(liste l1, liste l2, liste *l3){
	*l3=initListe();
	nombre nbr;

	while(!videListe(l1) && !videListe(l2))
	{
		if (entierNombre(nombreCourant(l1)) == entierNombre(nombreCourant(l2)))
		{
			nbr.entier=entierNombre(nombreCourant(l1));
			nbr.nbOcc=minNbOcc(nbOccNombre(nombreCourant(l1)),nbOccNombre(nombreCourant(l2)));
			inserQueue(nbr,l3);

			l1=suivCellule(l1);
			l2=suivCellule(l2);
		}
		else
		{
			if (entierNombre(nombreCourant(l1)) > entierNombre(nombreCourant(l2)))
			{
				l2=suivCellule(l2);
			}
			else
			{
				l1=suivCellule(l1);
			}
		}
	}
}

int PGCD(TabList Tab){
	int pgcd;
	int nbr,nbOcc;
	liste l,lPGCDtmp,lPGCD;

	pgcd=1;
	lPGCDtmp=(Tab.tab[0]).l;

	for (int i = 1; i < Tab.nbElem; i++)
	{
		l=Tab.tab[i].l;
		intersecListe(l,lPGCDtmp,&lPGCD);
		lPGCDtmp=lPGCD;
	}

	while(!videListe(lPGCD))
	{
		pgcd=pgcd*(pow(entierNombre(lPGCD->nbr),nbOccNombre(lPGCD->nbr)));
		lPGCD=suivCellule(lPGCD);
	}
	return pgcd;
}

/*programme principale*/
int main (void) {
TabList Tab;
int pgcd;

srand(time(0));
TElement tab[TMAX]={200,75,25,1050};

printf("\033[34m" );
remplissageTabList(&Tab, tab, 4);
affTabList(Tab);

pgcd=PGCD(Tab);
printf("\033[32m" );
printf("le PGCD de [%d, %d, %d, %d] = %d\n", tab[0], tab[1], tab[2], tab[3], pgcd);
return 0;
}
