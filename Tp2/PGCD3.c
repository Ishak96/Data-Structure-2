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

typedef struct 
{
	liste teteNb;
	liste queueNb;
	int taille;
	
}listeNb;

typedef struct CelluleFact
{
	int monNombre;
	listeNb l;
	struct CelluleFact *suivantFact;
}*facteurNombres;

typedef struct 
{
	facteurNombres teteFac;
	facteurNombres queueFac;
	int taille;
}listeFact;
/*(1)premitive*/

facteurNombres suivFact(facteurNombres fac){
	return fac->suivantFact;
}

int monNombre(facteurNombres fac){
	return fac->monNombre;
}

listeNb facteurNombresListe(facteurNombres fac){
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

listeNb initListeNb(){
	listeNb lNb;

	lNb.teteNb=lNb.queueNb=NULL;
	lNb.taille=0;

	return lNb;
}

listeFact initListeFac(){
	listeFact lFac;

	lFac.teteFac=lFac.queueFac=NULL;
	lFac.taille=0;

	return lFac;
}

facteurNombres initFact(){
	return NULL;
}

/*(3) teste si une liste est vide ou non*/
int videListe(liste l){

	return l == NULL;

}

int videListeNb(listeNb lNb){
	return videListe(lNb.teteNb) && videListe(lNb.queueNb);
}

int videFact(facteurNombres fac){
	return fac == NULL;
}

int videListeFac(listeFact lFac){
	return videFact(lFac.teteFac) && videFact(lFac.queueFac);
}

/*(4) afficher les valeurs des differentes cellules de la liste*/
void affListe(listeNb l){
	while(!videListe(l.teteNb))
	{
		printf("(%d,%d) ",entierNombre(nombreCourant(l.teteNb)),nbOccNombre(nombreCourant(l.teteNb)));
	
		l.teteNb = suivCellule(l.teteNb);
	}
	printf("\n");
}

/*5) ajouter un nombre en tete de la liste */
void inserTete(nombre nbr , listeNb *lNb){

  liste cel;
  //creation de la cellule
  cel = (liste) malloc (sizeof(struct Cellule));
  cel->nbr = nbr;
  
  if(videListeNb(*lNb))
  {
  	lNb->teteNb=cel;
  	lNb->queueNb=cel;
  	cel->suivant=NULL;
  }
  else
  {
  	cel->suivant=lNb->teteNb;
  	lNb->teteNb=cel;
  } 
  lNb->taille=lNb->taille+1;
}

void inserTeteFac(int monNombre , listeNb l, listeFact *lFac){

  facteurNombres cel;
  //creation de la cellule
  cel = (facteurNombres) malloc (sizeof(struct CelluleFact));
  //remplissage de la cellule
  cel->monNombre = monNombre;
  cel->l = l;

  if(videListeFac(*lFac))
  {
  	lFac->teteFac=cel;
  	lFac->queueFac=cel;
  	cel->suivantFact=NULL;
  }
  else
  {
  	cel->suivantFact=lFac->teteFac;
  	lFac->teteFac=cel;
  }
  lFac->taille=lFac->taille+1;
}

/*7) ajouter un nombre en queue d'une liste */
void inserQueue(nombre nbr , listeNb *lNb){
  
  liste cel;
  //creation de la cellule
  cel = (liste) malloc (sizeof(struct Cellule));
  //remplissage de la cellule 
  cel->nbr = nbr;

  if( videListeNb(*lNb) )
  {
  	cel->suivant=NULL;
  	lNb->teteNb=lNb->queueNb=cel;
  }
  else
  {
  	cel->suivant=(lNb->queueNb)->suivant;
  	(lNb->queueNb)->suivant=cel;
  	lNb->queueNb=cel;
  }
  lNb->taille=lNb->taille+1;
}

void inserQueueFac(int monNombre, listeNb l, listeFact *lFac){
	facteurNombres cel;
  	//creation de la cellule
  	cel = (facteurNombres) malloc (sizeof(struct CelluleFact));
  	//remplissage de la cellule 
  	cel->l = l;
  	cel->monNombre = monNombre;

  if( videListeFac(*lFac) )
  {
  	cel->suivantFact=NULL;
  	lFac->teteFac=lFac->queueFac=cel;
  }
  else
  {
  	cel->suivantFact=(lFac->queueFac)->suivantFact;
  	(lFac->queueFac)->suivantFact=cel;
  	lFac->queueFac=cel;
  }
  lFac->taille=lFac->taille+1;
}

void decompEntier(listeFact *fac, TElement nbr){
	listeNb l;
	int nbOcc,d,rn,num;

	l=initListeNb();
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
	
	if (videListeNb(l))
	{
		nombre monNombre={nbr,1};
		inserTete(monNombre,&l);
	}
	
	inserQueueFac(num,l,fac);
}

void remplissageFact(listeFact *fac, TElement *tab, int n){
	*fac=initListeFac();
	for (int i = 0; i < n; i++)
	{
		decompEntier(fac,tab[i]);
	}
}

void affFact(listeFact fac){
	while( fac.taille>0 )
	{
		printf("%d|->", (fac.teteFac)->monNombre);
		affListe((fac.teteFac)->l);
		fac.teteFac=(fac.teteFac)->suivantFact;
		fac.taille=fac.taille-1;
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

void intersecListe(listeNb l1, listeNb l2, listeNb *l3){
	*l3=initListeNb();
	nombre nbr;

	while(!videListe(l1.teteNb) && !videListe(l2.teteNb))
	{
		if (entierNombre(nombreCourant(l1.teteNb)) == entierNombre(nombreCourant(l2.teteNb)))
		{
			nbr.entier=entierNombre(nombreCourant(l1.teteNb));
			nbr.nbOcc=minNbOcc(nbOccNombre(nombreCourant(l1.teteNb)),nbOccNombre(nombreCourant(l2.teteNb)));
			inserQueue(nbr,l3);

			l1.teteNb=suivCellule(l1.teteNb);
			l2.teteNb=suivCellule(l2.teteNb);
		}
		else
		{
			if (entierNombre(nombreCourant(l1.teteNb)) > entierNombre(nombreCourant(l2.teteNb)))
			{
				l2.teteNb=suivCellule(l2.teteNb);
			}
			else
			{
				l1.teteNb=suivCellule(l1.teteNb);
			}
		}
	}
}

int PGCD(listeFact fac){
	int pgcd;
	int nbr,nbOcc;
	listeNb l,lPGCDtmp,lPGCD;

	pgcd=1;
	lPGCDtmp=(fac.teteFac)->l;
	fac.teteFac=(fac.teteFac)->suivantFact;

	while( !videFact(fac.teteFac))
	{
		l=(fac.teteFac)->l;
		intersecListe(l,lPGCDtmp,&lPGCD);
		lPGCDtmp=lPGCD;
		fac.teteFac=(fac.teteFac)->suivantFact;
	}

	while(!videListe(lPGCD.teteNb))
	{
		pgcd=pgcd*(pow(entierNombre((lPGCD.teteNb)->nbr),nbOccNombre((lPGCD.teteNb)->nbr)));
		lPGCD.teteNb=(lPGCD.teteNb)->suivant;
	}
	return pgcd;
}

/*programme principale*/
int main (void) {
listeFact fac;
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