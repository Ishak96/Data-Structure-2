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
	struct Cellule *precedent;
}*liste;

typedef struct
{
	liste tete;
	liste queue;
	int taille;
}FLCDS;

/*		<<<<<<< Primitives de bases sur les listes circulaires >>>>>>>		*/
liste cellule_Suivante(liste l){
	return l->suivant;
}

liste cellule_Precedente(liste l){
	return l->precedent;
}

TElement get_donnee_liste(liste l){
	return l->donnee;
}

liste get_tete_FLCDS(FLCDS flc){
	return flc.tete;
}

liste get_queue_FLCDS(FLCDS flc){
	return flc.queue;
}

int get_taille_FLCDS(FLCDS flc){
	return flc.taille;
}

TElement get_donnee_FLCDS(FLCDS flc){
	return get_donnee_liste(flc.tete);
}

liste get_first(FLCDS flc){
	return get_tete_FLCDS(flc)->suivant;
}

void afficher_FLCDS(FLCDS flc){
	flc.tete=get_first(flc);
	for(int i=1; i<get_taille_FLCDS(flc); i++)
	{
		if(i<get_taille_FLCDS(flc)-1)
			printf("%d|",get_donnee_liste(flc.tete));
		else
			printf("%d",get_donnee_liste(flc.tete));

		flc.tete=(flc.tete)->suivant;
	}
	printf("\n");
}

/*2)-vide_FLCDS(flc) renvoie vrai si la FLCDS est vide, faux sinon*/
int vide_FLCDS(FLCDS flc){
	return get_taille_FLCDS(flc)==0;
}

/*3)-sommet_FLCDS(flc) retourne l'élément au sommet de la FLCDS*/
/*	!!!! précondition:!vide-FLCDS(flc) !!!!	   */
liste sommet_FLCDS(FLCDS flc){
	return get_tete_FLCDS(flc);
}

/*4)-emfiler-FLCDS(elt,flc) ajoute un élément au sommet de la file*/
/*a)-insertion dans une FLCDS vide*/
void inser_FLCDS_Vide(TElement elt, FLCDS *flc){
	liste cel;
	
	cel = (liste) malloc (sizeof(struct Cellule));
	cel->donnee=elt;
	
	cel->suivant=cel;
	cel->precedent=cel;
	flc->tete=cel;
	flc->queue=cel;
	flc->taille=1;
}

void emfiler_FLCDS(TElement elt, FLCDS *flc){
	liste cel;
	
	if(vide_FLCDS(*flc))
		inser_FLCDS_Vide(elt,flc);
	else
	{	
		cel = (liste) malloc (sizeof(struct Cellule));
		cel->donnee=elt;

		cel->suivant=get_tete_FLCDS(*flc);
		cel->precedent=flc->queue;
		(flc->queue)->suivant=cel;
		flc->queue=cel;
		(flc->tete)->precedent=get_queue_FLCDS(*flc);
		flc->taille=(flc->taille)+1;
	}
}

/*5)-defiler_FLCDS(flc) suprrime de la file le premier élément*/
void defiler_FLCDS(FLCDS *flc){
	liste cel;

	cel=get_first(*flc);
	(flc->tete)->suivant=get_first(*flc)->suivant;
	(flc->queue)->suivant=get_tete_FLCDS(*flc);
	(flc->tete)->precedent=get_queue_FLCDS(*flc);

	free(cel);
	flc->taille=get_taille_FLCDS(*flc)-1;
}

/*1)-init_FLCDS(flc) initialise une FLCDS*/
FLCDS init_FLCDS(){
	FLCDS flc;

	inser_FLCDS_Vide(Sentinelle,&flc);

	return flc;
}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(){
	/*teste*/
	FLCDS flc;
	
	flc=init_FLCDS();
	
	for(int i=0; i<10; i++)
	{
		emfiler_FLCDS(i,&flc);
	}
	
	afficher_FLCDS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));
	printf("%d<-%d\n", get_donnee_liste(flc.tete), get_donnee_liste((flc.tete)->precedent));

	defiler_FLCDS(&flc);
	afficher_FLCDS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));
	printf("%d<-%d\n", get_donnee_liste(flc.tete), get_donnee_liste((flc.tete)->precedent));

return 0;
}

