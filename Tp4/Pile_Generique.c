#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

/*---- declaration des fonction génériques ----*/
typedef void (*TFct)(void* element);
typedef int (*comparElem)(void* element1, void* element2);

/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/
typedef void* TElement;

typedef struct Cellule{
	TElement donnee;
	struct Cellule *suivant;

}*liste;

typedef struct 
{
	int abscisse;
	int ordonne;
}coordonnees;

/* primitives pour les liste chaînées */
TElement valCellule(liste l){
	return l->donnee;

}

liste suivCellule(liste l){
	return l->suivant;

}
/* 		<<<<<<<	LES PILE >>>>>>>			*/
/*		{ représentation Chaînées }		*/
typedef liste pile;

/* primitives pour les piles */
TElement sommetPile(pile p){
	return p->donnee;

}

liste suivant(pile p){
	return p->suivant;

}

/*1) initialiser une pile*/
liste initPile(){
	return NULL;

}

/*2) teste si une pile est vide ou pas */
int videPile(pile p){
	return p == NULL;

}

/*4) determiner la hauteur d'une pile */
int hauteur(pile p){
  int lg = 0;
	while(!videPile(p)){
		lg = lg+1;
		p = suivant(p);
	}
	return lg;
}

/* 5) empiler "ajouter une valeur au sommet d'une pile" */
void empile(TElement X,int taile_TElement,pile *p){
pile cel;
	//création de la cellule
	cel = (pile) malloc (sizeof(struct Cellule));
	cel->donnee= malloc (taile_TElement);
	//remplissage de la cellule
	memcpy(cel->donnee, X, taile_TElement);
	//chainage
	cel->suivant = *p;
	*p = cel ;
}

/*6) depiler "retirer la valeur au sommet de la pile */
void depile(pile *p){
pile cel ;
	//préservation de la premier cellule de la liste 
	cel = *p;
	//realisation du chainage
	*p = suivant(*p);
	//liberation de la memeoire de la premier cellule
	free(cel);
}

/*-----			AFICHAGE DE PILES 			-----*/
void affInt(void *n){
	printf("%d ", *( int*)n);
}

void affCoord(void *n){
	printf("(%d,%d)|",(*((coordonnees *)n)).abscisse, (*((coordonnees *)n)).ordonne);
}
/*---------------------------------------------------*/
void affPile(pile p, TFct aff){
	while(!videPile(p)){
		aff(sommetPile(p));
		p = suivant(p);
	}
	printf("\n");
}

/*-----			COMPARAISON ENTRE LES ELEMENTS 			-----*/

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(int argc, char const *argv[])
{
	int size_int=sizeof(int);
	int size_coord=sizeof(coordonnees);
	pile p;
	int v1,v2,v3,v4;
	coordonnees c1={1,0};
	coordonnees c2={3,2};
	coordonnees c3={4,2};

	v1=14;
	v2=15;
	v3=1;
	v4=8;

	p=initPile();
	
	empile(&c1,size_coord,&p);
	empile(&c2,size_coord,&p);
	empile(&c3,size_coord,&p);
	
	affPile(p,affCoord);
	
	return 0;
}