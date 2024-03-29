#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include <string.h>
#include <time.h>

#define FUNC_ERROR -1
#define DEBUG 1

/*----  DECLARATION DE LA STRUCTURE   ----*/
typedef struct
{
	int cvc;
	char* nom;
	char* prenom;
	char* numero_carte;
	char* date;
}Client ;

typedef struct 
{
	Client donnee;
	int lien;
	int etat;
}Couple;

typedef struct 
{
	int taille;
	Couple* tabH;
}TableHachage;

int etat(int i, TableHachage th){
	#if(DEBUG > 0)
		if( th.tabH == NULL || i < 0 ){
			fprintf(stderr, "invalid argument ! : etat\n");
			return FUNC_ERROR;
		}
	#endif

	return th.tabH[i].etat;
}

int lien(int i, TableHachage th){
	#if(DEBUG > 0)
		if( th.tabH == NULL || i < 0 || etat(i, th) == -1 ){
			fprintf(stderr, "invalid argument ! : lien\n");
			return FUNC_ERROR;
		}
	#endif

	return th.tabH[i].lien;
}

Client client(int i, TableHachage th){
	Client cli = {0};
	#if(DEBUG > 0)
		if( th.tabH == NULL || i < 0 || etat(i, th) == -1 ){
			fprintf(stderr, "invalid argument i = %d! : client\n", i);
			return cli;
		}
	#endif

	return th.tabH[i].donnee;
}

int estEtat(int i, TableHachage th, int VEtat){
	#if(DEBUG > 0)
		if( th.tabH == NULL || i < 0 ){
			fprintf(stderr, "invalid argument i = %d ! : estEtat\n", i);
			return FUNC_ERROR;
		}
	#endif

	return ( etat(i, th) == VEtat );
}

int equals(Client c1, Client c2){
	#if(DEBUG > 0)
		if( c1.nom == NULL || c2.nom == NULL || c1.prenom == NULL || c2.prenom == NULL ){
			fprintf(stderr, "invalid argument ! : equals\n");
			return 0;
		}
	#endif

	return c1.cvc == c2.cvc && !strcmp(c1.nom, c2.nom) && !strcmp(c1.prenom, c2.prenom)
			&& !strcmp(c1.numero_carte, c2.numero_carte) && strcmp(c1.date, c2.date);
}

int alloc(TableHachage* th, int P, int R){
	#if(DEBUG > 0)
		if(P == 0 || R < 0){
			fprintf(stderr, "invalid argument ! : alloc\n");
			return FUNC_ERROR;
		}
	#endif

	th->taille = P + R;
	th->tabH = malloc( th->taille * sizeof(Couple) );

	#if(DEBUG > 0)
		if(th->tabH == NULL){
			fprintf(stderr, "can't allocate the tabel ! : alloc\n");
			return FUNC_ERROR;
		}
	#endif

	for(int i = 0; i < ( P + R ); i++){
		th->tabH[i].etat = -1;
		th->tabH[i].lien = 0;
	}

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

	if( estEtat(i, *th, 0) || estEtat(i, *th, -1) ){
		th->tabH[i].donnee = elt;
		th->tabH[i].lien = 0;
		th->tabH[i].etat = 1;

		return 0;
	}

	int l = lien(i, *th);
	int lib = 0;
	int arret = 0;

	while( !arret && l != 0 ){
		if( estEtat(i, *th, 0) && lib == 0 ){
			lib = i;
		}

		if( estEtat(i, *th, 1) && equals(client(i, *th), elt) ){
			arret = 1;
		}
		else{
			i = l;
			l = lien(i, *th);
		}
	}

	if( lib == 0 ){
		if( arret ){
			return 0;
		}

		int R = th->taille;

		while( R >= 0 && !estEtat(R, *th, -1) && !estEtat(i, *th, 0) ){
			R = R - 1;
		}

		if( R == 0 ){
			return 1;
		}

		th->tabH[i].lien = R;
		th->tabH[R].donnee = elt;
		th->tabH[R].etat = 1;

		return 0;
	}
	else{
		th->tabH[lib].donnee = elt;
		th->tabH[lib].etat = 1;

		if( arret ){
			th->tabH[i].etat = 0;
		}

		return 0;
	}

}

int rechercheHCO(Client elt, TableHachage th){
	#if(DEBUG > 0)
		if( th.tabH == NULL ){
			fprintf(stderr, "invalid argument ! : rechercheHCO\n");
			return FUNC_ERROR;
		}
	#endif

	int i = hach(elt, th.taille);
	int arret = 0;

	while( !estEtat(i, th, -1) && !estEtat(i, th, 0) && !equals(client(i, th), elt) && !arret ){
		if( lien(i, th) != 0 )
			i = lien(i, th);
		else
			arret = 1;
	}

	if( estEtat(i, th, 1) && equals(client(i, th), elt) )
		return i;
	else
		return FUNC_ERROR;

}

int suppHCO(Client elt, TableHachage* th){
	#if(DEBUG > 0)
		if( th->tabH == NULL ){
			fprintf(stderr, "invalid argument ! : suppHCO\n");
			return 0;
		}
	#endif

	int i = rechercheHCO(elt, *th);

	if( i > 0 ){
		th->tabH[i].etat = 0;
	}

	return i > 0;
}

Client get_client(char* numero_carte, TableHachage th){
	Client cli = {0};
	Client tmp = {0};

	#if(DEBUG > 0)
		if( th.tabH == NULL || numero_carte == NULL ){
			fprintf(stderr, "invalid argument ! : get_client\n");
			return cli;
		}
	#endif

	tmp.numero_carte = numero_carte;

	int i = hach(tmp, th.taille);
	int arret = 0;

	while( !estEtat(i, th, -1) && !estEtat(i, th, 0) && 
			strcmp(client(i, th).numero_carte, numero_carte) && !arret ) {
		if( lien(i, th) != 0 )
			i = lien(i, th);
		else
			arret = 1;
	}

	if( estEtat(i, th, 1) && !strcmp(client(i, th).numero_carte, numero_carte) )
		return client(i, th);
	else
		return cli;
}

/*PROGRAMME PRINCIPAL*/
int creatTable(char* data_file_name, TableHachage* th){
	FILE* data_file;
	int number_client, cvc;
	char numero_carte[16];
	char date[8];
	char nom[15];
	char prenom[15];

	#if(DEBUG > 0)
		if( data_file_name == NULL || th == NULL ){
			fprintf(stderr, "creatTable: invalid argument!\n");
			return FUNC_ERROR;
		}
	#endif

	data_file=fopen(data_file_name, "r+");

	#if(DEBUG > 0)
		if( data_file == NULL ){
			fprintf(stderr, "creatTable: open file!\n");
			return FUNC_ERROR;
		}
	#endif

	fscanf(data_file, "number of client = %d\n", &number_client);
	alloc(th, number_client, rand()%10 + 1);

	for(int i = 0; i < number_client; i++){
		fscanf(data_file, "%s %d %s %s %s\n", numero_carte, &cvc, date, prenom, nom);
		#if(DEBUG > 0)
			if( strlen(numero_carte) > 16 || strlen(date) > 7 || strlen(nom) > 15 || strlen(prenom) > 15 ){
				fprintf(stderr, "creatTable: ivalid argument on data file line %d!\n", i + 2);
				return FUNC_ERROR;		
			}
		#endif

		Client client = {0};
		client.cvc = cvc;
		client.nom = nom;
		client.prenom = prenom;
		client.numero_carte = numero_carte;
		client.date = date;

		/*printf("|----- %s ----\n", client.numero_carte);
		printf("|\t%d\t\n", client.cvc);
		printf("|\t%s\t\n", client.nom);
		printf("|\t%s\t\n", client.prenom);
		printf("|\t%s\t\n", client.date);
		printf("|-----------------------------\n");*/

		if( inserHCO(client, th) ){
			#if(DEBUG > 0)
				fprintf(stderr, "creatTable: overflow!\n");
				return FUNC_ERROR;	
			#endif			
		}
	}

	return 0;
}

int main(int argc, char **argv){
    srand(time(NULL));

    TableHachage th;

	if(argc < 2){
		fprintf(stderr, "main: invalid argument!\n");
		printf("usage: %s [data file]\n", argv[0]);
		return FUNC_ERROR;
	}

	if(creatTable(argv[1], &th) < 0){
		#if(DEBUG > 0)
			fprintf(stderr, "main: creatTable!\n");
			return FUNC_ERROR;	
		#endif
	}

	char* numero_carte = "4974279166009401";
	Client cli = get_client(numero_carte, th);

	if( cli.nom != NULL && cli.prenom != NULL && cli.numero_carte != NULL ){
		printf("|----- %s ----\n", numero_carte);
		printf("|\t%d\t\n", cli.cvc);
		printf("|\t%s\t\n", cli.nom);
		printf("|\t%s\t\n", cli.prenom);
		printf("|\t%s\t\n", cli.date);
		printf("|-----------------------------\n");
	}
	else{
		printf("Client avec numero de carte [ %s ] est introuvable\n", numero_carte);
	}

	return 0;
}