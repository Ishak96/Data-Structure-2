#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;
/*structure d'un arbreG*/
typedef struct noeud *ArbreG;
typedef struct Cellule *ListArbres; 
struct Cellule
{
	ArbreG premierFils;
	ListArbres suivant;
};
struct noeud
{
	TElement donne;
	ListArbres fils;
};

/*----  PRIMETIVES SUR ListArbres  ----*/
ListArbres initLIsteArbres(){
	return NULL;
}
void inserTete(ArbreG ag, ListArbres *la){

  ListArbres cel;
  //creation de la cellule
  cel = (ListArbres) malloc (sizeof(struct Cellule));
  if(cel==NULL)
  {
	printf("ERREUR INSER TETE\n");
	exit(0);
  }
  //remplissage de la cellule
  cel->premierFils = ag;
  //chainage 
  cel->suivant = *la;
  *la = cel;
}
int videListeArbres(ListArbres la){
	return 	la==NULL;
}
/*----	LES FILES 	----*/
typedef struct Cellule1
{
	ArbreG donnee;
	struct Cellule1 *suivant;
}*liste;
typedef struct 
{
	liste tete;
	liste queue;
}file;
file initFile(){
	file f;

	f.tete=f.queue=NULL;

	return f;
}
int videFile(file f){
	return f.tete==NULL;
}
ArbreG sommetFile(file f){
	return (f.tete)->donnee;
}
void emfiler(ArbreG elt, file *f){
	liste cel;

	cel=(liste)malloc(sizeof (struct Cellule1));

	cel->donnee=elt;
	cel->suivant=NULL;

	if (videFile(*f))
		f->tete=f->queue=cel;
	else
	{
		(f->queue)->suivant=cel;
		f->queue=cel;
	}
}
void defile(file *f){
	liste ff;

	ff=f->tete;

	(f->tete)=(f->tete)->suivant;

	free(ff);
}
/*----------ALGORITHMES----------*/
ArbreG initArbreG(){
	return NULL;
}
int videArbreG(ArbreG ag){
	return ag==NULL;
}
ArbreG creatFeuille(TElement elt){
	ArbreG f;

	f=(ArbreG)malloc(sizeof(struct noeud));
	if(f==NULL)
	{
		printf("ERREUR CREAT FEUILLE\n");
		exit(0);
	}

	f->fils=(ListArbres)malloc(sizeof(struct Cellule));
	f->fils=initLIsteArbres();
	f->donne=elt;

	return f;
}

ArbreG creatNoeud(TElement elt, ListArbres la){
	ArbreG nd;

	nd=(ArbreG)malloc(sizeof(struct noeud));
	if(nd==NULL)
	{
		printf("ERREUR CREAT NOEUD\n");
		exit(0);
	}

	nd->fils=(ListArbres)malloc(sizeof(struct Cellule));
	nd->fils=initLIsteArbres();
	nd->fils=la;
	nd->donne=elt;

	return nd;
}

ArbreG creatArbreG(){
	ArbreG ag0,ag1,ag2,ag3,ag4,ag5,ag6,ag7,ag8,ag9,ag10;
	ListArbres la;
	
	la=initLIsteArbres();
	//creation des feuilles de l'arbre
	ag10=creatFeuille(0);
	ag9=creatFeuille(4);
	ag8=creatFeuille(-6);
	ag7=creatFeuille(10);
	ag5=creatFeuille(2);
	ag4=creatFeuille(5);
	ag1=creatFeuille(9);

	//creation des neouds de l'arbre
	inserTete(ag9,&la);
	inserTete(ag10,&la);
	ag6=creatNoeud(11,la);
	la=initLIsteArbres();
	
	inserTete(ag7,&la);
	inserTete(ag8,&la);
	ag3=creatNoeud(3,la);
	la=initLIsteArbres();

	inserTete(ag4,&la);
	inserTete(ag5,&la);
	inserTete(ag6,&la);
	ag2=creatNoeud(8,la);
	la=initLIsteArbres();

	inserTete(ag1,&la);
	inserTete(ag2,&la);
	inserTete(ag3,&la);
	ag0=creatNoeud(15,la);

	la=initLIsteArbres();

	return ag0;
}
void parcoursPrefixe(ArbreG ag){
	ListArbres la;
	if (!videArbreG(ag))
	{
		printf("%d\t",ag->donne);
		la=ag->fils;
		while(!videListeArbres(la))
		{
			parcoursPrefixe(la->premierFils);
			la=la->suivant;
		}
	}
}
void parcoursPostfixe(ArbreG ag){
	ListArbres la;
	if (!videArbreG(ag))
	{
		la=ag->fils;
		while(!videListeArbres(la))
		{
			parcoursPostfixe(la->premierFils);
			la=la->suivant;
		}
		printf("%d\t",ag->donne);
	}
}

void parcoursLargeur(ArbreG ag){
	file f;
	ArbreG sf;
	ListArbres la;

	f=initFile();
	emfiler(ag,&f);

	while(!videFile(f))
	{
		sf=sommetFile(f);
		defile(&f);

		printf("%d\t", sf->donne);
		la=sf->fils;
		while(!videListeArbres(la))
		{
			emfiler(la->premierFils,&f);
			la=la->suivant;
		}
	}
	printf("\n");
}

void tailleArbeG(ArbreG ag, int *s){
	ListArbres la;
	int s1;
	
	if (!videArbreG(ag))
	{
		*s+=1;
		la=ag->fils;
		while(!videListeArbres(la))
		{
			s1=0;
			tailleArbeG(la->premierFils,&s1);
			la=la->suivant;
			*s+=s1;
		}
	}	
}
int estFeuille(ArbreG ag){
	return videListeArbres(ag->fils);
}
void nbFeuilles(ArbreG ag, int *nbF){
	int nbFeuilles1;
	ListArbres la;

	if (!videArbreG(ag))
	{
		if(estFeuille(ag))
			*nbF+=1;

		la=ag->fils;
		while(!videListeArbres(la))
		{
			nbFeuilles1=0;
			nbFeuilles(la->premierFils,&nbFeuilles1);
			la=la->suivant;
			*nbF+=nbFeuilles1;
		}
	}
}
void rechercheElt(TElement elt, ArbreG ag, int *existe){
	int existe1;
	ListArbres la;
	
	if (videArbreG(ag))
		*existe=0;
	else
	{
		if(ag->donne==elt)
			*existe=1;
		else
		{
			la=ag->fils;
			while(!videListeArbres(la))
			{
				existe1=0;
				rechercheElt(elt, la->premierFils, &existe1);
				la=la->suivant;
				*existe=*existe||existe1;
			}
		}
	}
}
void ppeArbreG(ArbreG ag, TElement *ppe){
	TElement ppe1;ListArbres la;

	if (!videArbreG(ag))
	{
		if (estFeuille(ag))
			*ppe=ag->donne;
		else
		{
			la=ag->fils;
			while(!videListeArbres(la))
			{
				ppeArbreG(la->premierFils,&ppe1);
				la=la->suivant;
				if(ppe1<*ppe)
					*ppe=ppe1;
			}
		}	
	}
}
int degreNoueud(ArbreG ag){
	int degre;
	ListArbres la;

	degre=0;
	la=ag->fils;
	while(!videListeArbres(la))
	{
		if (!videArbreG(la->premierFils))
			degre+=1;
		la=la->suivant;
	}

	return degre;
}

void degreArbre(ArbreG ag, int *degre){
	int degre1;
	ListArbres la;

	if(videArbreG(ag))
		*degre=0;
	else
	{
		*degre=degreNoueud(ag);
		la=ag->fils;
		while(!videListeArbres(la))
		{
			degreArbre(la->premierFils, &degre1);
			if(*degre<degre1)
				*degre=degre1;
			la=la->suivant;
		}
	}
}
/*PROGRAMME PRINCIPAL*/
int main(int argc, char const *argv[])
{
	ArbreG ag;
	int s,nbF,eltR,existe,degre;
	TElement ppe;

	ag=initArbreG();
	ag=creatArbreG();
	s=0;
	nbF=0;
	existe=0;
	degre=0;
	eltR=4;

	tailleArbeG(ag,&s);
	nbFeuilles(ag,&nbF);
	rechercheElt(eltR,ag,&existe);
	ppeArbreG(ag,&ppe);
	degreArbre(ag,&degre);

	printf("le parcours prefixe\n");
	parcoursPrefixe(ag);
	printf("\n");

	printf("le parcours postfixe\n");
	parcoursPostfixe(ag);
	printf("\n");

	printf("le parcours en largeur\n");
	parcoursLargeur(ag);
	printf("\n");

	printf("la taille de l'arbre est :%d\n", s);
	printf("le nombre de feuilles de l'arbre est :%d\n", nbF);

	if (existe)
		printf("l'element :%d existe\n", eltR);
	else
		printf("l'element :%d n'existe pas\n", eltR);

	printf("le plus petit élément de l'arbre est :%d\n",ppe);
	printf("le degré de l'arbre est :%d\n", degre);

	return 0;
}