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

typedef struct Cellule
{
	nombre nbr;
	struct Cellule *suivant;
}*liste;

typedef struct CelluleFact
{
	int monNombre;
	liste l;
	struct CelluleFact *suivantFact;
}*facteurNombres;

/*(1)premitive*/

facteurNombres suivFact(facteurNombres fac){
	return fac->suivantFact;
}

int monNombre(facteurNombres fac){
	return fac->monNombre;
}

liste facteurNombresListe(facteurNombres fac){
	return fac->l;
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

/*(2)initialise une liste*/
liste initListe(){
	return NULL;

}

facteurNombres initFact(){
	return NULL;
}

/*(3) teste si une liste est vide ou non*/
int videListe(liste l){

	return l == NULL;

}

int videFact(facteurNombres fac){
	return fac == NULL;
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

void inserTeteFac(int monNombre , liste l, facteurNombres *fac){

  facteurNombres cel;
  //creation de la cellule
  cel = (facteurNombres) malloc (sizeof(struct CelluleFact));
  //remplissage de la cellule
  cel->monNombre = monNombre;
  cel->l = l;
  //chainage 
  cel->suivantFact = *fac;
  *fac = cel;
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

facteurNombres dernierFact(facteurNombres fac){
	if( !videFact(fac) )
	{
		while( !videFact(fac->suivantFact) )
		{
			fac = suivFact(fac);
		}
	}
	return fac;
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

void inserQueueFac(int monNombre, liste l, facteurNombres *fac){
  
  if( videFact(*fac) )
	inserTeteFac(monNombre, l, fac);
  else
  {
  	facteurNombres cel;
  	facteurNombres der;
  	der = dernierFact(*fac);
  	//creation de la cellule
  	cel = (facteurNombres) malloc (sizeof(struct CelluleFact));
  	//remplissage de la cellule 
  	cel->l = l;
  	cel->monNombre = monNombre;
  	//chainege
  	cel->suivantFact = NULL;
  	der->suivantFact = cel;
  }
}

void decompEntier(facteurNombres *fac, TElement nbr){
	liste l;
	int nbOcc,d,rn,num;

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
	
	inserQueueFac(num,l,fac);
}

void remplissageFact(facteurNombres *fac, TElement *tab, int n){
	*fac=initFact();
	for (int i = 0; i < n; i++)
	{
		decompEntier(fac,tab[i]);
	}
}

void affFact(facteurNombres fac){
	while( !videFact(fac) )
	{
		printf("%d|->", fac->monNombre);
		affListe(fac->l);
		fac=fac->suivantFact;
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

int PGCD(facteurNombres fac){
	int pgcd;
	int nbr,nbOcc;
	liste l,lPGCDtmp,lPGCD;

	pgcd=1;
	lPGCDtmp=fac->l;
	fac=fac->suivantFact;

	while(!videFact(fac))
	{
		l=fac->l;
		intersecListe(l,lPGCDtmp,&lPGCD);
		lPGCDtmp=lPGCD;
		fac=fac->suivantFact;
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
facteurNombres fac;
int pgcd;

srand(time(0));
TElement tab[TMAX]={200,75,25,1050};

printf("\033[34m" );
remplissageFact(&fac, tab, 4);
affFact(fac);

pgcd=PGCD(fac);
printf("\033[32m" );
printf("le PGCD de [%d, %d, %d, %d] = %d\n", tab[0], tab[1], tab[2], tab[3], pgcd);
return 0;
}