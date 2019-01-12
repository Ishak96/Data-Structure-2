#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

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
}FLCD;

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

liste get_tete_FLCD(FLCD flc){
	return flc.tete;
}

liste get_queue_FLCD(FLCD flc){
	return flc.queue;
}

int get_taille_FLCD(FLCD flc){
	return flc.taille;
}

TElement get_donnee_FLCD(FLCD flc){
	return get_donnee_liste(flc.tete);
}

void afficher_FLCD(FLCD flc){
	for(int i=0; i<get_taille_FLCD(flc); i++)
	{
		if(i<get_taille_FLCD(flc)-1)
			printf("%d|",get_donnee_liste(flc.tete));
		else
			printf("%d",get_donnee_liste(flc.tete));

		flc.tete=(flc.tete)->suivant;
	}
	printf("\n");
}

/*1)-init_FLCD(flc) initialise une FLCD*/
FLCD init_FLCD(){
	FLCD flc;

	flc.tete=NULL;
	flc.queue=NULL;
	flc.taille=0;

	return flc;
}

/*2)-vide_FLCD(flc) renvoie vrai si la FLCD est vide, faux sinon*/
int vide_FLCD(FLCD flc){
	return get_taille_FLCD(flc)==0;
}

/*3)-sommet_FLCD(flc) retourne l'élément au sommet de la FLCD*/
/*	!!!! précondition:!vide-FLCD(flc) !!!!	   */
liste sommet_FLCD(FLCD flc){
	return get_tete_FLCD(flc);
}

/*4)-emfiler-FLCD(elt,flc) ajoute un élément au sommet de la file*/
/*a)-insertion dans une FLCD vide*/
void inser_FLCD_Vide(TElement elt, FLCD *flc){
	liste cel;
	
	cel = (liste) malloc (sizeof(struct Cellule));
	cel->donnee=elt;
	
	cel->suivant=cel;
	cel->precedent=cel;
	flc->tete=cel;
	flc->queue=cel;
	flc->taille=1;
}

void emfiler_FLCD(TElement elt, FLCD *flc){
	liste cel;
	
	if(vide_FLCD(*flc))
		inser_FLCD_Vide(elt,flc);
	else
	{	
		cel = (liste) malloc (sizeof(struct Cellule));
		cel->donnee=elt;

		cel->suivant=get_tete_FLCD(*flc);
		cel->precedent=flc->queue;
		(flc->queue)->suivant=cel;
		flc->queue=cel;
		(flc->tete)->precedent=get_queue_FLCD(*flc);
		flc->taille=(flc->taille)+1;
	}
}

/*5)-defiler_FLCD(flc) suprrime de la file le premier élément*/
void defiler_FLCD(FLCD *flc){
	liste cel;

	cel=get_tete_FLCD(*flc);
	flc->tete=get_tete_FLCD(*flc)->suivant;
	(flc->queue)->suivant=get_tete_FLCD(*flc);
	(flc->tete)->precedent=get_queue_FLCD(*flc);

	free(cel);
	flc->taille=get_taille_FLCD(*flc)-1;
}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(){
	/*teste*/
	FLCD flc;
	
	flc=init_FLCD();
	
	for(int i=0; i<10; i++)
	{
		emfiler_FLCD(i,&flc);
	}
	
	afficher_FLCD(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));
	printf("%d<-%d\n", get_donnee_liste(flc.tete), get_donnee_liste((flc.tete)->precedent));

	defiler_FLCD(&flc);
	afficher_FLCD(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));
	printf("%d<-%d\n", get_donnee_liste(flc.tete), get_donnee_liste((flc.tete)->precedent));

return 0;
}
