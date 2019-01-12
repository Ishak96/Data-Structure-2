#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

#define MAX_NB 100

typedef void* TElement;
typedef void (*AffFct)(void* element);
typedef int (*comparElem)(void* element1, void* element2);

/*----	VALEURS DES TElement  ----*/
int donneINT(TElement elem){
	if(elem == NULL)
		return 0;
	return *( int*)elem;
}
/*----  COMPARAISON ENTR LES TElement  ----*/
int comparINT(TElement elem1, TElement elem2){
	int e1,e2;

	e1=donneINT(elem1);
	e2=donneINT(elem2);

	return e1-e2;
}
/*----  AFFICHAGE DES TElement  ----*/
void affINT(TElement elem){
	int e;

	e=donneINT(elem);
	printf("%d\n", e);
}
/*	<<<<<<< STRUCTURE DES ARBRES BINAIRES >>>>>>>		*/

typedef struct noeud{
	TElement donnee;
	struct noeud * filsG;
	struct noeud * filsD;
}*ArbreOrdonne;
/*1)primetive des ARBRES BINAIRE */
TElement donnee(ArbreOrdonne a){
	return a->donnee;
}
ArbreOrdonne filsG(ArbreOrdonne a){
	return a->filsG;
}
ArbreOrdonne filsD(ArbreOrdonne a){
	return a->filsD;
}
/*2)les differents fonction utiles vu en CM */
/*a)initialiser un Arbre */
ArbreOrdonne initArbre(){
	return NULL;
}
/*b)teste si un Arbre Binaire est vide ou pas */
int videArbre(ArbreOrdonne a){
	return (a == NULL);
}
/*c)creation d'une feuille */
ArbreOrdonne creatFeuille(TElement X, int taille_TElement){
 ArbreOrdonne f;
 f = (ArbreOrdonne) malloc (sizeof(struct noeud));
 f->donnee = malloc (taille_TElement);
 memcpy(f->donnee, X, taille_TElement);

 f->filsG = f->filsD = NULL;
 return f;
}
/*d)creation d'un noeud */
ArbreOrdonne creatNoeud(TElement X,int taille_TElement,ArbreOrdonne fG, ArbreOrdonne fD){
 ArbreOrdonne nd;
 
 nd = (ArbreOrdonne) malloc (sizeof(struct noeud));
 nd->donnee = malloc (taille_TElement);
 memcpy(nd->donnee, X, taille_TElement);

 nd->filsG = fG;
 nd->filsD = fD;
 return nd;
}
/*e)les parcours en profondeur*/
/*Parcour Préfixe*/	/*(RGD)*/
void parcourPrefixe(ArbreOrdonne a,AffFct aff){
	if(!videArbre(a)){
		aff(donnee(a));
		parcourPrefixe(a->filsG,aff);
		parcourPrefixe(a->filsD,aff);
	}
}
/*Parcour Infixe*/	/*(GRD)*/
void parcourInfixeTrie(ArbreOrdonne a,int *i,TElement tab,int te){
	if(!videArbre(a)){
		parcourInfixeTrie((a->filsG),i,tab,te);
		memcpy(tab+(*i)*te,donnee(a), te);
		*i = *i+1;
		parcourInfixeTrie((a->filsD),i,tab,te);
	}
}
void parcourInfixe(ArbreOrdonne a,AffFct aff){
	if(!videArbre(a)){
		parcourInfixe((a->filsG),aff);
		aff(donnee(a));
		parcourInfixe((a->filsD),aff);
	}
}
/*Parcour Postfixe*/	/*(GDR)*/
void parcourPostfixe(ArbreOrdonne a,AffFct aff){
	if(!videArbre(a)){
		parcourPostfixe(a->filsG,aff);
		parcourPostfixe(a->filsD,aff);
		aff(donnee(a));
	}
}
/*g) Determiner le nombre de feuilles dans un arbre binaire*/
/*la fonction est feuille qui teste si un noeud est une feuille ou pas */
int estFeuille(ArbreOrdonne a){
	return videArbre(filsG(a)) && videArbre(filsD(a));
}
/*3)recherche d'un element donnee dans un arbre donnee */
int rechercheEltArbreOrdonne(ArbreOrdonne a ,TElement X, comparElem comp){
	if(videArbre(a))
		return 0;
	else
		if(comp(donnee(a),X)==0)//==
			return 1;
		else
			if(comp(donnee(a),X)==-1)//<
				return rechercheEltArbreOrdonne(filsD(a),X,comp);
			else
				return rechercheEltArbreOrdonne(filsG(a),X,comp);
}
/*4)insrtion d'un element donnee dans un arbre donnee */
void inserEltArbreOrdonne(ArbreOrdonne *a,TElement X,int taille_TElement,comparElem comp){
	if(videArbre(*a)) {
		*a = creatFeuille(X,taille_TElement);
	} else {
		if( comp(X,donnee(*a))<=0)//>
			inserEltArbreOrdonne( &((*a)->filsG),X , taille_TElement,comp);
		else
			inserEltArbreOrdonne( &((*a)->filsD),X , taille_TElement,comp);
	}
}
void suppArbre(ArbreOrdonne *a){
	if(!videArbre(*a)){
		suppArbre(& ((*a)->filsG) );
		suppArbre(& ((*a)->filsD) );
		free(*a);
		*a=NULL;
	}
}
/*9)trier un tableau composé de n elements (entier) en utilisant un arbre binaire Ordonnee */
void trieTableauArbreOrdonnee(int n,TElement tab, int taille_TElement, comparElem comp){
 ArbreOrdonne a = initArbre();
 TElement elt;
	for(int i=0 ; i<n ; i++){
		elt=tab+i*taille_TElement;
		inserEltArbreOrdonne(&a,elt,sizeof(TElement),comp);
	}
	n = 0;
	parcourInfixeTrie(a,&n,tab,taille_TElement);
	suppArbre(&a);
}
/*	<<<<<<< PROGRAMME PRINCIPALE >>>>>>> */

int main (void) {
 int tab[MAX_NB] = {17,7,19,5,2,8,13,20,29,11,4,33,9,6,12,16,4,3,18};

 int size_int=sizeof(int);
 int size_TElem=sizeof(TElement);

 printf("TElement = int\n");
 printf("---------------------------------------------------------------\n"); 
 
 printf("avant\n");
 for(int i=0 ; i<19 ; i++){
	printf("%d ",tab[i]);
 }
 printf("\n");

 printf("---------------------------------------------------------------\n");
 
 printf("apres\n");
 trieTableauArbreOrdonnee(19,&tab,size_int,comparINT);
 for(int i=0 ; i<19 ; i++){
	printf("%d ",tab[i]); 
 }
 printf("\n");
 printf("END\n");

return 0;
}