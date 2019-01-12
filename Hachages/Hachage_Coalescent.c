#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>

typedef int TElement;
/*----  DECLARATION DE LA STRUCTURE   ----*/
typedef struct 
{
	TElement donnee;
	int lien;
}Couple;

typedef struct 
{
	int taille;
	Couple *tabH;
}TableHachage;

/*ALGORITHME DE HACHAGE*/
int hach(TElement elt){
	return elt%10;
}

/*PROGRAMME PRINCIPAL*/
int main(int argc, char const *argv[]){

	TElement tabElt[10]={7,11,122,90,76,88,45,650,88,77};
	TableHachage Hached;

	return 0;
}
