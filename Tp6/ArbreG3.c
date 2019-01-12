#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;
typedef struct noeud *ArbreG;
struct noeud
{
	TElement donnee;
	ArbreG fils;
	ArbreG freres;
};

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
ArbreG creatFeuille(TElement elt, ArbreG freresAnie){
	ArbreG f;

	f=(ArbreG)malloc(sizeof(struct noeud));
	if(f==NULL)
	{
		printf("ERREUR CREAT FEUILLE\n");
		exit(0);
	}
	f->fils=NULL;
	f->freres=freresAnie;
	f->donnee=elt;

	return f;
}
ArbreG creatNoeud(TElement elt, ArbreG filsAnie, ArbreG freresAnie){
	ArbreG nd;

	nd=(ArbreG)malloc(sizeof(struct noeud));
	if (nd==NULL)
	{
		printf("ERREUR CREAT NOEUD\n");
		exit(0);		
	}
	nd->fils=filsAnie;
	nd->freres=freresAnie;
	nd->donnee=elt;

	return nd;
}
ArbreG creatArbreG(){
	ArbreG ag0,ag1,ag2,ag3,ag4,ag5,ag6,ag7,ag8,ag9,ag10;

	//creation des feuilles de l'arbre
	ag9=creatFeuille(4,NULL);
	ag10=creatFeuille(0,ag9);
	ag7=creatFeuille(10,NULL);
	ag8=creatFeuille(-6,ag7);
	ag4=creatFeuille(5,NULL);
	ag5=creatFeuille(2,ag4);
	ag1=creatFeuille(9,NULL);
	//creation des noeuds de l'arbre
	ag6=creatNoeud(11,ag10,ag5);
	ag2=creatNoeud(8,ag6,ag1);
	ag3=creatNoeud(3,ag8,ag2);
	ag0=creatNoeud(15,ag3,NULL);

	return ag0;
}
void parcoursPrefixe(ArbreG ag){
	ArbreG ac;

	printf("%d\t", ag->donnee);
	ac=ag->fils;

	while(!videArbreG(ac))
	{
		parcoursPrefixe(ac);
		ac=ac->freres;
	}
}
void parcoursPostfixe(ArbreG ag){
	ArbreG ac;

	ac=ag->fils;

	while(!videArbreG(ac))
	{
		parcoursPostfixe(ac);
		ac=ac->freres;
	}

	printf("%d\t", ag->donnee);
}
void parcoursLargeur(ArbreG ag){
	file f;
	ArbreG sf;
	ArbreG ac;

	f=initFile();
	emfiler(ag,&f);

	while(!videFile(f))
	{
		sf=sommetFile(f);
		defile(&f);

		printf("%d\t", sf->donnee);
		ac=sf->fils;

		while(!videArbreG(ac))
		{
			emfiler(ac,&f);
			ac=ac->freres;
		}
	}
	printf("\n");
}
int tailleArbreG(ArbreG ag){
	if(videArbreG(ag))
		return 0;
	else
		return 1+tailleArbreG(ag->fils)+tailleArbreG(ag->freres);
}
int estFeuille(ArbreG ag){
	return ag->fils==NULL;
}
int nbFeuilles(ArbreG ag){
	if(videArbreG(ag))
		return 0;
	else
		if(estFeuille(ag))
			return 1+nbFeuilles(ag->freres);
		else
			return nbFeuilles(ag->fils)+nbFeuilles(ag->freres);
}
int rechercheElt(TElement elt,ArbreG ag){
	if(videArbreG(ag))
		return 0;
	else
		if(ag->donnee==elt)
			return 1;
		else
			return rechercheElt(elt, ag->fils)
					|| rechercheElt(elt, ag->freres);
}
TElement ppeArbreG(ArbreG ag){
	TElement ppF,ppFR,pp;
	ArbreG ac;

	if (estFeuille(ag))
		return ag->donnee;
	else
	{
		pp=ag->donnee;
		ac=ag->fils;

		while(!videArbreG(ac))
		{
			ppF=ppeArbreG(ac);
			if(ppF<pp)
				pp=ppF;

			ac=ac->freres;
		}

		return pp;
	}
}
int degreNoueud(ArbreG ag){
	ArbreG ac;
	int degre=0;
	if (videArbreG(ag->fils))
		return 0;
	else
	{
		ac=ag->fils;
		while(!videArbreG(ac))
		{
			degre+=1;
			ac=ac->freres;
		}
		return degre;
	}
}
int degreArbreG(ArbreG ag){
	int degre,degre1;
	ArbreG ac;

	if(videArbreG(ag))
		return 0;
	else
	{
		degre=degreNoueud(ag);
		ac=ag->fils;

		while(!videArbreG(ac))
		{
			degre1=degreNoueud(ac);
			if(degre<degre1)
				degre=degre1;

			ac=ac->freres;
		}
		return degre;
	}
}
/*PROGRAMME PRINCIPAL*/
int main(int argc, char const *argv[]){
	ArbreG ag;
	int eltR=0;

	ag=initArbreG();
	ag=creatArbreG();

	printf("le parcours prefixe\n");
	parcoursPrefixe(ag);
	printf("\n");

	printf("le parcours postfixe\n");
	parcoursPostfixe(ag);
	printf("\n");

	printf("le parcours en largeur\n");
	parcoursLargeur(ag);
	printf("\n");

	printf("la taille de l'arbre est :%d\n", tailleArbreG(ag));
	printf("le nombre de feuilles de l'arbre est :%d\n", nbFeuilles(ag));

	if (rechercheElt(eltR,ag))
		printf("l'element :%d existe\n", eltR);
	else
		printf("l'element :%d n'existe pas\n", eltR);

	printf("le plus petit élément de l'arbre est :%d\n",ppeArbreG(ag));
	printf("le degré de l'arbre est :%d\n", degreArbreG(ag));

	return 0;
}