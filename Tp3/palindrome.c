#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

/* 		<<<<<<<	LES LISTE CIRCULAIRES + FLCS + Pile>>>>>>>			*/
typedef char TElement;

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

typedef liste Pile;

/*		<<<<<<< Primitives de bases sur les listes circulaires >>>>>>>		*/
liste cellule_Suivante(liste l){
	return l->suivant;
}

TElement get_donnee_liste(liste l){
	return l->donnee;
}

liste init_Liste(){
	return NULL;
}

int vide_Liste(liste l){
	return l==NULL;
}

void inserTete(TElement elt , liste *l){
  liste cel;
  //creation de la cellule
  cel = (liste) malloc (sizeof(struct Cellule));
  //remplissage de la cellule
  cel->donnee = elt;
  //chainage 
  cel->suivant = *l;
  *l = cel;
}

void suppTete(liste *l){
  liste cel ;
  //conservation de la premiere cellule
  cel = *l;
  //chainage
  *l = cellule_Suivante(*l);
  free(cel);
}

void delListe(liste *l){
  while( !vide_Liste(*l) )
  {
	suppTete(l);
  }
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
			printf("%c|",get_donnee_liste(flc.tete));
		else
			printf("%c",get_donnee_liste(flc.tete));

		flc.tete=(flc.tete)->suivant;
	}
	printf("\n");
}

/*---------------------------------------------------------------------------------------------------------------------*/
Pile suivant(Pile p){
	return p->suivant;
}

/*1)-init_FLCS(flc) initialise une FLCS*/
Pile init_Pile(){
	return NULL;
}

/*2)-vide_Pile(p) renvoie vrai si la pile est vide, faux sinon*/
int vide_Pile(Pile p){
	return p==NULL;
}

/*3)-sommet_Pile(p) retourne l'élément au sommet de la pile*/
/*	!!!! précondition:!vide-Pile(p) !!!!	   */
Pile sommet_Pile(Pile p){
	return p;
}

/*4)-emfiler(elt,flc) ajoute un élément au sommet de la pile*/
void empiler(TElement elt, Pile *p){
	Pile cel;
	
	//création de la cellule
	cel = (Pile) malloc (sizeof(struct Cellule));
	//remplissage de la cellule
	cel->donnee = elt;
	//chainage
	cel->suivant = *p;
	*p = cel ;
}

/*5)-depiler(p) suprrime de la pile le premier élément*/
void depiler(Pile *p){
	Pile cel ;
	
	//préservation de la premier cellule de la liste 
	cel = *p;
	//realisation du chainage
	*p = suivant(*p);
	//liberation de la memeoire de la premier cellule
	free(cel);
}

void dell_Pile(Pile *p){
	while(!vide_Pile(*p))
		depiler(p);
}

void affPile(Pile p){
	while(!vide_Pile(p)){
		printf("%c",sommet_Pile(p)->donnee);
		p = suivant(p);
	}
	printf("\n");
}

/*---------------------------------------------------------------------------------------------------------------------*/
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

void dell_FLCS(FLCS *flc){
	while(!vide_FLCS(*flc))
		defiler_FLCS(flc);
}

/*---------------------------------------------------------------------------------------------------------------------*/
/*		<<<<<<<< ALGORITHEMES DE TRAITEMENT >>>>>>>>		*/
void gener_Liste_mot(liste *l, char *mot, int n){
	for (int i = 0; i < n; i++)
	{
		inserTete(mot[i],l);
	}
}

void gener_FLCS_Pile(liste l, FLCS *flc, Pile *p){
	while(!vide_Liste(l)){
		emfiler_FLCS(l->donnee,flc);
		empiler((l)->donnee,p);
		l=cellule_Suivante(l);
	}
}

int palindrome(char *mot, int n){
	liste l;
	FLCS flc;
	Pile p;
	char sFLC,sP;
	int est_palindrome;

	est_palindrome=1;
	l=init_Liste();
	flc=init_FLCS();
	p=init_Pile();

	gener_Liste_mot(&l,mot,n);
	gener_FLCS_Pile(l,&flc,&p);
	delListe(&l);

	while((!vide_FLCS(flc) && !vide_Pile(p)) && est_palindrome)
	{
		sFLC=(flc.tete)->donnee;
		sP=p->donnee;
	
		if (sFLC!=sP)
		{
			est_palindrome=0;
		}
		
		defiler_FLCS(&flc);
		depiler(&p);
	}

	dell_FLCS(&flc);
	dell_Pile(&p);

	return est_palindrome;
}

/*		<<<<<<<< PROGRAME PRINCIPALE >>>>>>>>>			*/
int main(int argc, char *argv[]){

int palin,n;
char *mot=malloc(sizeof(char)*50);
char *nstr=malloc(sizeof(char)*5);
liste l;
FLCS flc;
Pile p;

strcat(mot,argv[1]);
strcat(nstr,argv[2]);
n=atoi(nstr);

palin=palindrome(mot,n);

if (palin)
{
	printf("le mot : %s est un palindrome\n", mot);
}
else
{
	printf("le mot : %s n'est pas un palindrome\n", mot);
}

return 0;
}