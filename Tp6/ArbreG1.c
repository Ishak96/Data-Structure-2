#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;
/*structure d'un arbreG*/
typedef struct noeud *ArbreG;
struct noeud
{
	TElement donnee;
	ArbreG *fils;
};
/*----	LES FILES 	----*/
typedef struct Cellule
{
	ArbreG donnee;
	struct Cellule *suivant;
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

	cel=(liste)malloc(sizeof (struct Cellule));

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
ArbreG creatFeuille(int nbFils, TElement elt){
	ArbreG f;

	f=(ArbreG)malloc(sizeof(struct noeud));
	if(f==NULL)
	{
		printf("ERREUR CREAT FEUILLE\n");
		exit(0);
	}

	f->fils=(ArbreG*)malloc(nbFils*sizeof(ArbreG));
	for(int i=0; i<nbFils; i++)
		f->fils[i]=NULL;

	f->donnee=elt;
	return f;
}
ArbreG creatNoeud(int nbFils, ArbreG *tfils, TElement elt){
	ArbreG nd;

	nd=(ArbreG)malloc(sizeof(struct noeud));
	if(nd==NULL)
	{
		printf("ERREUR CREAT NOEUD\n");
		exit(0);
	}

	nd->fils=(ArbreG*)malloc(nbFils*sizeof(ArbreG));
	for (int i = 0; i < nbFils; i++)
	{
		nd->fils[i]=tfils[i];
	}

	nd->donnee=elt;
	return nd;
}
ArbreG creatArbreG(int nbFils){
	ArbreG ag0,ag1,ag2,ag3,ag4,ag5,ag6,ag7,ag8,ag9,ag10;
	ArbreG *tfils;

	//creation des feuilles de l'arbre
	ag10=creatFeuille(nbFils,0);
	ag9=creatFeuille(nbFils,4);
	ag8=creatFeuille(nbFils,-6);
	ag7=creatFeuille(nbFils,10);
	ag5=creatFeuille(nbFils,2);
	ag4=creatFeuille(nbFils,5);
	ag1=creatFeuille(nbFils,9);

	//creation des neouds de l'arbre
	tfils=(ArbreG*)malloc(nbFils*sizeof(ArbreG));
	tfils[0]=ag10;
	tfils[1]=ag9;
	tfils[2]=NULL;
	ag6=creatNoeud(nbFils, tfils, 11);

	tfils[0]=ag8;
	tfils[1]=ag7;
	tfils[2]=NULL;
	ag3=creatNoeud(nbFils, tfils, 3);

	tfils[0]=ag6;
	tfils[1]=ag5;
	tfils[2]=ag4;
	ag2=creatNoeud(nbFils, tfils, 8);

	tfils[0]=ag3;
	tfils[1]=ag2;
	tfils[2]=ag1;
	ag0=creatNoeud(nbFils, tfils, 15);

	return ag0;
}

void parcoursPrefixe(int nbFils,ArbreG ag){
	if (!videArbreG(ag)){
		printf("%d\t",ag->donnee);
		for (int i = 0; i < nbFils; i++)
			parcoursPrefixe(nbFils, ag->fils[i]);
	}
}

void parcoursPostfixe(int nbFils,ArbreG ag){
	if (!videArbreG(ag)){
		for (int i = 0; i < nbFils; i++)
			parcoursPostfixe(nbFils, ag->fils[i]);
		printf("%d\t",ag->donnee);
	}
}
void parcoursLargeur(int nbFils,ArbreG ag){
	file f;
	ArbreG sf; 

	f=initFile();
	emfiler(ag,&f);

	while(!videFile(f))
	{
		sf=sommetFile(f);
		defile(&f);

		printf("%d\t", sf->donnee);

		for (int i = 0; i < nbFils; i++)
		{
			if (!videArbreG(sf->fils[i]))
				emfiler(sf->fils[i],&f);
		}
	}
	printf("\n");
}

void tailleArbreG(int nbFils,ArbreG ag, int *s){
	int i,s1;
	if (!videArbreG(ag))
	{
		*s+=1;
		for ( i = 0; i < nbFils; i++){
			s1=0;
			tailleArbreG(nbFils, ag->fils[i],&s1);
			*s+=s1;
		}
	}
}

int estFeuille(int nbFils, ArbreG ag){
	int i;
	i=0;

	while(videArbreG(ag->fils[i]) && i<nbFils)
		i++;

	return i>=nbFils;
}		

void nbFeuilles(int nbFils, ArbreG ag, int *nbF){
	int i,nbFeuilles1;

	if (!videArbreG(ag))
	{
		if(estFeuille(nbFils,ag))
			*nbF+=1;

		for ( i = 0; i < nbFils; i++){
			nbFeuilles1=0;
			nbFeuilles(nbFils, ag->fils[i],&nbFeuilles1);
			*nbF+=nbFeuilles1;
		}
	}
}
void rechercheElt(TElement elt, int nbFils, ArbreG ag, int *existe){
	int existe1;
	
	if (videArbreG(ag))
		*existe=0;
	else
	{
		if(ag->donnee==elt)
			*existe=1;
		else
		{
			for (int i = 0; i < nbFils; i++)
			{
				existe1=0;
				rechercheElt(elt,nbFils, ag->fils[i],&existe1);
				*existe=*existe||existe1;
			}
		}
	}
}
void ppeArbreG(int nbFils, ArbreG ag, TElement *ppe){
	TElement ppe1;
	if (!videArbreG(ag))
	{
		if (estFeuille(nbFils,ag))
			*ppe=ag->donnee;
		else
		{
			for (int i = 0; i < nbFils; i++)
			{
				ppeArbreG(nbFils, ag->fils[i],&ppe1);
				if(ppe1<*ppe)
					*ppe=ppe1;
			}
		}	
	}
}
int degreNoueud(int nbFils ,ArbreG ag){
	int degre;

	degre=0;
	for (int i = 0; i < nbFils; i++)
	{
		if (!videArbreG(ag->fils[i]))
			degre+=1;
	}

	return degre;
}

void degreArbre(int nbFils, ArbreG ag, int *degre){
	int degre1;

	if(videArbreG(ag))
		*degre=0;
	else
	{
		*degre=degreNoueud(nbFils,ag);
		for (int i = 0; i < nbFils; i++)
		{
			degreArbre(nbFils, ag->fils[i], &degre1);
			if(*degre<degre1)
				*degre=degre1;
		}
	}
}

/*PROGRAMME PRINCIPAL*/
int main(int argc, char const *argv[])
{
	int nbFils,s,nbF,eltR,existe,degre;
	ArbreG ag;
	TElement ppe;

	nbFils=3;
	s=0;
	nbF=0;
	existe=0;
	degre=0;
	eltR=4;
	ag=initArbreG();

	ag=creatArbreG(nbFils);
	
	printf("le parcours prefixe\n");
	parcoursPrefixe(3,ag);
	printf("\n");

	printf("le parcours postfixe\n");
	parcoursPostfixe(3,ag);
	printf("\n");

	printf("le parcours en largeur\n");
	parcoursLargeur(3,ag);
	printf("\n");
	
	tailleArbreG(nbFils,ag,&s);
	nbFeuilles(nbFils,ag,&nbF);
	rechercheElt(eltR,nbFils,ag,&existe);
	ppeArbreG(nbFils,ag,&ppe);
	degreArbre(nbFils,ag,&degre);

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