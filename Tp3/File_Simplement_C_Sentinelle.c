#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define Sentinelle 1000

/* 		<<<<<<<	LES LISTE CIRCULAIRES >>>>>>>			*/
typedef int TElement;

typedef struct Cellule
{
	TElement donnee;
	struct Cellule *suivant;
}*liste;

typedef struct
{
	liste tete;
	liste queue;
	int taille;
}FLCSS;

/*		<<<<<<< Primitives de bases sur les listes circulaires >>>>>>>		*/
liste cellule_Suivante(liste l){
	return l->suivant;
}

TElement get_donnee_liste(liste l){
	return l->donnee;
}

liste get_tete_FLCSS(FLCSS flc){
	return flc.tete;
}

liste get_queue_FLCSS(FLCSS flc){
	return flc.queue;
}

int get_taille_FLCSS(FLCSS flc){
	return flc.taille;
}

liste get_first(FLCSS flc){
	return get_tete_FLCSS(flc)->suivant;
}

TElement get_donnee_FLCSS(FLCSS flc){
	return get_donnee_liste(flc.tete);
}

void afficher_FLCSS(FLCSS flc){
	flc.tete=get_first(flc);
	for(int i=1; i<get_taille_FLCSS(flc); i++)
	{
		if(i<get_taille_FLCSS(flc)-1)
			printf("%d|",get_donnee_liste(flc.tete));
		else
			printf("%d",get_donnee_liste(flc.tete));

		flc.tete=(flc.tete)->suivant;
	}
	printf("\n");
}

/*2)-vide_FLCSS(flc) renvoie vrai si la FLCSS est vide, faux sinon*/
int vide_FLCSS(FLCSS flc){
	return get_taille_FLCSS(flc)==0;
}

/*3)-sommet_FLCSS(flc) retourne l'élément au sommet de la FLCSS*/
/*	!!!! précondition:!vide-FLCSS(flc) !!!!	   */
liste sommet_FLCSS(FLCSS flc){
	return get_tete_FLCSS(flc);
}

/*4)-emfiler-FLCSS(elt,flc) ajoute un élément au sommet de la file*/
/*a)-insertion dans une FLCSS vide*/
void inser_FLCSS_Vide(TElement elt, FLCSS *flc){
	liste cel;
	
	cel = (liste) malloc (sizeof(struct Cellule));
	cel->donnee=elt;
	
	cel->suivant=cel;
	flc->tete=cel;
	flc->queue=cel;
	flc->taille=1;
}

void emfiler_FLCSS(TElement elt, FLCSS *flc){
	liste cel;
	
	if(vide_FLCSS(*flc))
		inser_FLCSS_Vide(elt,flc);
	else
	{	
		cel = (liste) malloc (sizeof(struct Cellule));
		cel->donnee=elt;

		cel->suivant=get_tete_FLCSS(*flc);
		(flc->queue)->suivant=cel;
		flc->queue=cel;
		flc->taille=(flc->taille)+1;
	}
}

/*5)-defiler_FLCSS(flc) suprrime de la file le premier élément*/
void defiler_FLCSS(FLCSS *flc){
	liste cel;

	cel=get_first(*flc);
	(flc->tete)->suivant=get_first(*flc)->suivant;
	(flc->queue)->suivant=get_tete_FLCSS(*flc);

	free(cel);
	flc->taille=get_taille_FLCSS(*flc)-1;
}

/*1)-init_FLCSS(flc) initialise une FLCSS*/
void init_FLCSS(FLCSS *flc){
	
	inser_FLCSS_Vide(Sentinelle,flc);
}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(){
	/*teste*/
	FLCSS flc;
	
	init_FLCSS(&flc);
	
	for(int i=0; i<10; i++)
	{
		emfiler_FLCSS(i,&flc);
	}
	
	afficher_FLCSS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));

	defiler_FLCSS(&flc);
	afficher_FLCSS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));

return 0;
}

