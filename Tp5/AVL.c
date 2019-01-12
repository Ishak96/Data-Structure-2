#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

#define MAX_NB 100

typedef int TElement;
/*	<<<<<<< STRUCTURE DES ARBRES BINAIRES >>>>>>>		*/
typedef struct noeud{
	TElement donnee;
	struct noeud * filsG;
	struct noeud * filsD;
	int hauteur;
}*AVL;
/*1)primetive des ARBRES BINAIRE */
TElement donnee(AVL a){
	return a->donnee;
}
AVL filsG(AVL a){
	return a->filsG;
}
AVL filsD(AVL a){
	return a->filsD;
}
/*2)les differents fonction utiles vu en CM */
/*a)initialiser un AVL */
AVL initAVL(){
	return NULL;
}
/*b)teste si un AVL est vide ou pas */
int videAVL(AVL a){
	return (a == NULL);
}
int hauteur(AVL a){
	if (videAVL(a))
		return -1;
	else
		return a->hauteur;
}
int factEqulibre(AVL a){
	return hauteur(filsD(a))-hauteur(filsG(a));
}
/*c)creation d'une feuille */
AVL creatFeuille(TElement X){
 AVL f;

 f = (AVL) malloc (sizeof(struct noeud));
 f->donnee = X;
 f->filsG = f->filsD = NULL;
 f->hauteur=0;

 return f;
}
/*d)creation d'un noeud */
AVL creatNoeud(TElement X, AVL fG, AVL fD){
 AVL nd;

 nd = (AVL) malloc (sizeof(struct noeud));
 nd->donnee = X;
 nd->filsG = fG;
 nd->filsD = fD;

 return nd;
}
/*e)les parcours en profondeur*/
/*Parcour Préfixe*/	/*(RGD)*/
void parcourPrefixe(AVL a){
	if(!videAVL(a)){
		printf("{%d ,h=%d, fact=%d}\n",donnee(a), hauteur(a), factEqulibre(a));
		parcourPrefixe(a->filsG);
		parcourPrefixe(a->filsD);
	}
}
/*Parcour Infixe*/	/*(GRD)*/
void parcourInfixeTrie(AVL a,int *i,TElement *tab){
	if(!videAVL(a)){
		parcourInfixeTrie((a->filsG),i,tab);
		tab[*i] = donnee(a);
		*i = *i+1;
		parcourInfixeTrie((a->filsD),i,tab);
	}
}
void parcourInfixe(AVL a){
	if(!videAVL(a)){
		parcourInfixe((a->filsG));
		printf("{%d ,h=%d, fact=%d}\n",donnee(a), hauteur(a), factEqulibre(a));
		parcourInfixe((a->filsD));
	}
}
/*Parcour Postfixe*/	/*(GDR)*/
void parcourPostfixe(AVL a){
	if(!videAVL(a)){
		parcourPostfixe(a->filsG);
		parcourPostfixe(a->filsD);
		printf("{%d ,h=%d, fact=%d}\n",donnee(a), hauteur(a), factEqulibre(a));
	}
}
/*g) Determiner le nombre de feuilles dans un arbre binaire*/
/*la fonction est feuille qui teste si un noeud est une feuille ou pas */
int estFeuille(AVL a){
	return videAVL(filsG(a)) && videAVL(filsD(a));
}
/*3)recherche d'un element donnee dans un arbre donnee */
int rechercheEltAVL(AVL a ,TElement X){
	if(videAVL(a))
		return 0;
	else
		if(donnee(a) == X)
			return 1;
		else
			if(donnee(a) < X)
				return rechercheEltAVL(filsD(a),X);
			else
				return rechercheEltAVL(filsG(a),X);
}
/*		ROTATION DANS LES AVL 		*/
/*----------------------------------*/
int MAX(int a, int b){
	int max=a;

	if(max<b)
		max=b;
	return max;
}
AVL rotationG(AVL a){
	AVL p,u,q,v,w;

	p=a;
	u=filsG(a);
	q=filsD(a);
	v=filsG(q);
	w=filsD(q);

	q->filsG=p;
	p->filsD=v;

	p->hauteur=1+MAX(hauteur(u),hauteur(v));
	q->hauteur=1+MAX(hauteur(p),hauteur(w));

	return q;
}
AVL rotationD(AVL a){
	AVL p,u,q,v,w;

	p=a;
	q=filsG(a);
	w=filsD(a);
	u=filsG(q);
	v=filsD(q);

	q->filsD=p;
	p->filsG=v;

	p->hauteur=1+MAX(hauteur(w),hauteur(v));
	q->hauteur=1+MAX(hauteur(p),hauteur(u));

	return q;
}
AVL rotationDG(AVL a){
	a->filsD=rotationD(filsD(a));
	return rotationG(a);
}
AVL rotationGD(AVL a){
	a->filsG=rotationG(filsG(a));
	return rotationD(a);
}
/*4)insrtion d'un element donnee dans un arbre donnee */
void inserEltAVL(AVL *a,TElement X){
	int fact;
	AVL fg,fd;
	if(videAVL(*a))
	{
		*a = creatFeuille(X);
	}
	else
	{
		if(donnee(*a) > X)
		{
			inserEltAVL( (&((*a)->filsG)),X );
			fact=factEqulibre(*a);
			if (fact==-2)
			{
				if (factEqulibre(filsG(*a))==-1)
				{
					*a=rotationD(*a);
				}
				else
				{
					*a=rotationGD(*a);
				}
			}
		}
		else
		{
			if( donnee(*a) < X)
			{
				inserEltAVL( (&((*a)->filsD)),X );
				fact=factEqulibre(*a);
				if (fact==2)
				{
					if(factEqulibre(filsD(*a))==1)
					{
						*a=rotationG(*a);
					}
					else
					{
						*a=rotationDG(*a);
					}
				}
			}
		}
		fg=filsG(*a);
		fd=filsD(*a);

		(*a)->hauteur=1+MAX(hauteur(fg),hauteur(fd));
	}
}
void suppArbre(AVL *a){
	if(!videAVL(*a)){
		suppArbre(& ((*a)->filsG) );
		suppArbre(& ((*a)->filsD) );
		free(*a);
		*a=NULL;
	}
}
/*9)trier un tableau composé de n elements (entier) en utilisant un arbre binaire Ordonnee */
void trieTableauAVL(int n,TElement *tab){
 AVL a;

 a = initAVL();
	for(int i=0 ; i<n ; i++){
		inserEltAVL(&a,tab[i]);	
	}

	n = 0;
	parcourInfixe(a);
	parcourInfixeTrie(a,&n,tab);
	suppArbre(&a);
}
int est_AVL(AVL a){
	if (videAVL(a) || estFeuille(a))
		return 1;
	else
		if (factEqulibre(a)==2 || factEqulibre(a)==-2)
			return 0;
		else
			return est_AVL(filsG(a))&&est_AVL(filsD(a));
}

/*	<<<<<<< PROGRAMME PRINCIPALE >>>>>>> */
int main (void) {

srand(time(NULL));

AVL a;
int tab[20]={10,6,7,8,9,15,20,13,12};
int n=9;

a=initAVL();
for (int i = 0; i < n; i++)
{
	inserEltAVL(&a,tab[i]);
}

if (est_AVL(a))
	printf("est un AVL\n");
else
	printf("n'est pas un AVL\n");

for (int i = 0; i < n; i++)
{
	printf("%d\t", tab[i]);
}
printf("\n");

trieTableauAVL(n,tab);

for (int i = 0; i < n; i++)
{
	printf("%d\t", tab[i]);
}
printf("\n");

return 0;
}