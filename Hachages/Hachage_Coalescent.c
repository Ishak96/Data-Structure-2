#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include <string.h>

#define FUNC_ERROR -1

typedef enum {VIDE, LIBRE, OCCUPE} TEtat;

/*----  DECLARATION DE LA STRUCTURE   ----*/
typedef struct
{
	int cvc;
	char* nom;
	char* prenom;
	char numero_carte[16];
	char date[7];
}Client ;

typedef struct 
{
	Client donnee;
	int lien;
	TEtat etat;
}Couple;

typedef struct 
{
	int taille;
	Couple* tabH;
}TableHachage;

TEtat etat(int i, TableHachage th){
	if( th.tabH == NULL || i < 0 ){
		fprintf(stderr, "invalid argument ! : etat\n");
		return FUNC_ERROR;
	}

	return th.tabH[i].etat;
}

int lien(int i, TableHachage th){
	if( th.tabH == NULL || i < 0 || etat(i, th) == VIDE ){
		fprintf(stderr, "invalid argument ! : lien\n");
		return FUNC_ERROR;
	}

	return th.tabH[i].lien;
}

Client client(int i, TableHachage th){
	Client cli = {0};
	if( th.tabH == NULL || i < 0 || etat(i, th) == VIDE ){
		fprintf(stderr, "invalid argument ! : client\n");
		return cli;
	}

	return th.tabH[i].donnee;
}

int estEtat(int i, TableHachage th, TEtat VEtat){
	if( th.tabH == NULL || i < 0 ){
		fprintf(stderr, "invalid argument ! : estEtat\n");
		return FUNC_ERROR;
	}

	return ( etat(i, th) == VEtat );
}

int equals(Client c1, Client c2){

	if( c1.nom == NULL || c2.nom == NULL || c1.prenom == NULL || c2.prenom == NULL ){
		fprintf(stderr, "invalid argument ! : equals\n");
		return 0;
	}

	return c1.cvc == c2.cvc && !strcmp(c1.nom, c2.nom) && !strcmp(c1.prenom, c2.prenom)
			&& !strcmp(c1.numero_carte, c2.numero_carte) && strcmp(c1.date, c2.date);
}

int alloc(TableHachage* th, int P, int R){
	if(P == 0 || R < 0){
		fprintf(stderr, "invalid argument ! : alloc\n");
		return FUNC_ERROR;
	}

	th->tabH = malloc( ( P + R) * sizeof(Couple) );
	th->taille = P + R;

	if(th->tabH == NULL){
		fprintf(stderr, "can't allocate the tabel ! : alloc\n");
		return FUNC_ERROR;
	}

	for(int i = 0; i < ( P + R ); i++)
		th->tabH[i].etat = LIBRE;

	return 0;
}

/*ALGORITHME DE HACHAGE*/
int hach(Client elt, int M){
	int hached = 0;

	for(int i = 0; elt.numero_carte[i] != '\0'; i++)
		hached += elt.numero_carte[i];

	hached %= M;

	return hached;
}

int inserHCO(Client elt, TableHachage* th){
	int i = hach(elt, th->taille);

	if( estEtat(i, *th, LIBRE) ){
		th->tabH[i].donnee = elt;
		th->tabH[i].lien = 0;
		th->tabH[i].etat = OCCUPE;

		return 0;
	}

	int l = lien(i, *th);
	int lib = 0;
	int arret = 0;

	while( !arret && l == 0 ){
		if( estEtat(i, *th, LIBRE) && lib == 0 )
			lib = i;

		if( estEtat(i, *th, OCCUPE) && equals(client(i, *th), elt) )
			arret = 1;
		else{
			i = l;
			l = lien(i, *th);
		}
	}

	if( lib == 0 ){
		if( arret )
			return 0;

		int R = th->taille;

		while( R >= 0 && !estEtat(R, *th, VIDE) )
			R = R - 1;

		if( R == 0 )
			return 1;

		th->tabH[i].lien = R;
		th->tabH[R].donnee = elt;
		th->tabH[R].etat = OCCUPE;

		return 0;
	}
	else{
		th->tabH[lib].donnee = elt;
		th->tabH[lib].etat = OCCUPE;

		if( arret )
			th->tabH[i].etat = LIBRE;

		return 0;
	}

}

int rechercheHCO(Client elt, TableHachage th){
	if( th.tabH == NULL ){
		fprintf(stderr, "invalid argument ! : rechercheHCO\n");
		return FUNC_ERROR;
	}

	int i = hach(elt, th.taille);
	int arret = 0;

	while( !estEtat(i, th, VIDE) && !estEtat(i, th, LIBRE) && !equals(client(i, th), elt) && !arret ){
		if( lien(i, th) != 0 )
			i = lien(i, th);
		else
			arret = 1;
	}

	if( estEtat(i, th, OCCUPE) && equals(client(i, th), elt) )
		return i;
	else
		return FUNC_ERROR;

}

int suppHCO(Client elt, TableHachage* th){
	if( th->tabH == NULL ){
		fprintf(stderr, "invalid argument ! : suppHCO\n");
		return 0;
	}

	int i = rechercheHCO(elt, *th);

	if( i > 0 ){
		th->tabH[i].etat = LIBRE;
	}

	return i > 0;
}

/*PROGRAMME PRINCIPAL*/
int main(int argc, char const *argv[]){
	

	return 0;
}