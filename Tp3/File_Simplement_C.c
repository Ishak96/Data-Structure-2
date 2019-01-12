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
}*liste;

typedef struct
{
	liste tete;
	liste queue;
	int taille;
}FLCS;

/*		<<<<<<< Primitives de bases sur les listes circulaires >>>>>>>		*/
liste cellule_Suivante(liste l){
	return l->suivant;
}

TElement get_donnee_liste(liste l){
	return l->donnee;
}

liste get_tete_FLCS(FLCS flc){
	return flc.tete;
}

liste get_queue_FLCS(FLCS flc){
	return flc.queue;
}

int get_taille_FLCS(FLCS flc){
	return flc.taille;
}

TElement get_donnee_FLCS(FLCS flc){
	return get_donnee_liste(flc.tete);
}

void afficher_FLCS(FLCS flc){
	for(int i=0; i<get_taille_FLCS(flc); i++)
	{
		if(i<get_taille_FLCS(flc)-1)
			printf("%d|",get_donnee_liste(flc.tete));
		else
			printf("%d",get_donnee_liste(flc.tete));

		flc.tete=(flc.tete)->suivant;
	}
	printf("\n");
}

/*1)-init_FLCS(flc) initialise une FLCS*/
FLCS init_FLCS(){
	FLCS flc;

	flc.tete=NULL;
	flc.queue=NULL;
	flc.taille=0;

	return flc;
}

/*2)-vide_FLCS(flc) renvoie vrai si la FLCS est vide, faux sinon*/
int vide_FLCS(FLCS flc){
	return get_taille_FLCS(flc)==0;
}

/*3)-sommet_FLCS(flc) retourne l'élément au sommet de la FLCS*/
/*	!!!! précondition:!vide-FLCS(flc) !!!!	   */
liste sommet_FLCS(FLCS flc){
	return get_tete_FLCS(flc);
}

/*4)-emfiler-FLCS(elt,flc) ajoute un élément au sommet de la file*/
/*a)-insertion dans une FLCS vide*/
void inser_FLCS_Vide(TElement elt, FLCS *flc){
	liste cel;
	
	cel = (liste) malloc (sizeof(struct Cellule));
	cel->donnee=elt;
	
	cel->suivant=cel;
	flc->tete=cel;
	flc->queue=cel;
	flc->taille=1;
}

void emfiler_FLCS(TElement elt, FLCS *flc){
	liste cel;
	
	if(vide_FLCS(*flc))
		inser_FLCS_Vide(elt,flc);
	else
	{	
		cel = (liste) malloc (sizeof(struct Cellule));
		cel->donnee=elt;

		cel->suivant=get_tete_FLCS(*flc);
		(flc->queue)->suivant=cel;
		flc->queue=cel;
		flc->taille=(flc->taille)+1;
	}
}

/*5)-defiler_FLCS(flc) suprrime de la file le premier élément*/
void defiler_FLCS(FLCS *flc){
	liste cel;

	cel=get_tete_FLCS(*flc);
	flc->tete=get_tete_FLCS(*flc)->suivant;
	(flc->queue)->suivant=get_tete_FLCS(*flc);

	free(cel);
	flc->taille=get_taille_FLCS(*flc)-1;
}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(){
	/*teste*/
	FLCS flc;
	
	flc=init_FLCS();
	
	for(int i=0; i<10; i++)
	{
		emfiler_FLCS(i,&flc);
	}
	
	afficher_FLCS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));

	defiler_FLCS(&flc);
	afficher_FLCS(flc);
	printf("%d->%d\n", get_donnee_liste(flc.queue), get_donnee_liste((flc.queue)->suivant));

return 0;
}
