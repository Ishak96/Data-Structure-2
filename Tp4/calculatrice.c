#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include<string.h>

#define ZERO '0'
#define NEUF '9'
#define MAX_NB 1000

typedef enum {OPERAND,OPERATEUR} Tcaracter;
typedef void* TElement;

int parenthese(char car){
	return car == '(';
}
int separateur(char car){
	return car == ' ' || car== ',' ;
}
int chiffre(char car){
	return car >= ZERO && car <= NEUF;
}
int operateur(char car){
	return car == '+' || car == '-' || car == '*' || car == '/';
}
int parentheseFermente(char car){
	return car == ')';
}
int finChar(char car){
	return (car == '\0');
}

/*  <<<<<<< STRUCTRE DU TYPE D4ELEMENT DE L'ARBRE >>>>>>>  */
typedef struct 
{
	Tcaracter typeCar;
	union
	{
		char operation;
		double operand;
	}nCar;
}TElementArbre;

/*	<<<<<<< STRUCTURE DES ARBRES BINAIRES >>>>>>>		*/
typedef struct noeud{
	TElementArbre donnee;
	struct noeud * filsG;
	struct noeud * filsD;

}*Arbre;

/*1)primetive des ARBRES BINAIRE */
TElementArbre donnee(Arbre a){
	return a->donnee;
}
Arbre filsG(Arbre a){
	return a->filsG;
}
Arbre filsD(Arbre a){
	return a->filsD;
}
/*2)les differents fonction utiles vu en CM */
/*a)initialiser un Arbre */
Arbre initArbre(){
	return NULL;
}
/*b)teste si un Arbre Binaire est vide ou pas */
int videArbre(Arbre a){
	return (a == NULL);
}
/*c)creation d'une feuille */
Arbre creatFeuille(TElementArbre X){
 Arbre f;
 
 f = (Arbre) malloc (sizeof(struct noeud));
 f->donnee = X;
 f->filsG = f->filsD = NULL;
 return f;
}
int estFeuille(Arbre a){
	return videArbre(filsG(a)) && videArbre(filsD(a));
}
/*d)creation d'un noeud */
Arbre creatNoeud(TElementArbre X, Arbre fG, Arbre fD){
 Arbre nd;

 nd = (Arbre) malloc (sizeof(struct noeud));
 nd->donnee = X;
 nd->filsG = fG;
 nd->filsD = fD;
 return nd;
}
/*Parcour Postfixe*/	/*(GDR)*/
void parcourPostfixe(Arbre a){
	if(!videArbre(a)){
		parcourPostfixe(a->filsG);
		parcourPostfixe(a->filsD);
		if (donnee(a).typeCar==OPERATEUR)
		{
			printf("%c ",donnee(a).nCar.operation);
		}
		else
		{
			printf("%g ",donnee(a).nCar.operand);	
		}
	}
}
/* 		<<<<<<<	LES LISTE chaînéés >>>>>>>			*/
typedef struct Cellule{
	TElement donnee;
	struct Cellule *suivant;
}*liste;
/* primitives pour les liste chaînées */
TElement valCellule(liste l){
	return l->donnee;
}
liste suivCellule(liste l){
	return l->suivant;
}
/********************************************/
/* 		<<<<<<<	LES PILE Génerique >>>>>>>			*/
/*		{ représentation Chaînées }		*/
typedef liste pile;
/* primitives pour les piles */
TElement sommetPile(pile p){
	return p->donnee;
}
pile suivant(pile p){
	return p->suivant;
}
/*1) initialiser une pile*/
pile initPile(){
	return NULL;
}
/*2) teste si une pile est vide ou pas */
int videPile(pile p){
	return p == NULL;
}
/* 3) empiler "ajouter une valeur au sommet d'une pile" */
void empile(TElement X,int taile_TElement,pile *p){
pile cel;
	//création de la cellule
	cel = (pile) malloc (sizeof(pile));
	cel->donnee= malloc (taile_TElement);
	//remplissage de la cellule
	memcpy(cel->donnee, X, taile_TElement);
	//chainage
	cel->suivant = *p;
	*p = cel ;
}
/*4) depiler "retirer la valeur au sommet de la pile */
void depile(pile *p){
pile cel ;
	//préservation de la premier cellule de la liste 
	cel = *p;
	//realisation du chainage
	*p = suivant(*p);
	//liberation de la memeoire de la premier cellule
	free(cel);
}
/*	<<<<<<< APPLICATION >>>>>>>	*/
float operand(char car){
	return car - '0';
}
float eval(char car , float OperandG , float OperandD){
	switch( car ){
		case '+' : return (OperandG + OperandD) ;break;
		case '-' : return (OperandG - OperandD);break;
		case '*' : return (OperandG * OperandD);break;
		case '/' : if(OperandG != 0){
				return (OperandG / OperandD);
			   }else{
				printf(" E : on peut pas diviser par ZERO\n");
			   }
		break;
		default : printf("E : aucune operation \n"); 
	}
}
Arbre transformExpArbre(char *exp){
 pile pc,pa;
 int Erreur,i,size_arbre,size_car;
 char car,oper;
 Arbre fg,fd,f,nd;
 TElementArbre Tar;
 double div,chif,mul;

 pc = initPile();
 pa = initPile();

 size_arbre=sizeof(Arbre);
 size_car=sizeof(char);

 i = 0;
 div = 0.1;
 mul = 10;

 car = exp[i];
 Erreur = 0;
	while( !finChar(car) && !Erreur ){
		if( parenthese(car) ||  separateur(car) ){
				i++;
		}else
			if( chiffre(car) || car=='.'){
				
				Tar.typeCar=OPERAND;
				if (car=='.')
				{
					i++;
					chif=0;
					while(!operateur((exp[i])) && !finChar(exp[i]) && !parentheseFermente(exp[i]))
					{
						chif+=div*(exp[i]-'0');
						div*=0.1;
						i++;
					}
					div=0.1;					
				}	
				else
				{
					chif=car-'0';
					i++;
					if (exp[i]=='.')
					{
						i++;
						while(!operateur((exp[i])) && !finChar(exp[i]) && !parentheseFermente(exp[i]))
						{
							chif+=div*(exp[i]-'0');
							div*=0.1;
							i++;
						}
						div=0.1;
					}
					else
					{
						if (chiffre(exp[i]))
						{
							while(!operateur((exp[i])) && !finChar(exp[i]) && !parentheseFermente(exp[i]))
							{
								chif*=mul;
								chif+=(exp[i]-'0');
								i++;
								if (exp[i]=='.')
								{
									i++;
									while(!operateur((exp[i])) && !finChar(exp[i]) && !parentheseFermente(exp[i]))
									{
										chif+=div*(exp[i]-'0');
										div*=0.1;
										i++;
									}
									div=0.1;
								}
							}
						}
					}
				}
				Tar.nCar.operand=chif;
				f = creatFeuille(Tar);	
				empile(&f,size_arbre,&pa);
			}else
				if( operateur(car) ){
					empile(&car,size_car,&pc);
					i++;
				}else
					if( parentheseFermente(car) ){			
						fd = (*((Arbre *)sommetPile(pa)));
						depile(&pa);

						fg = (*((Arbre *)sommetPile(pa)));
						depile(&pa);

						oper = (*((char *)sommetPile(pc)));
						depile(&pc);

						Tar.typeCar=OPERATEUR;
						Tar.nCar.operation=oper;

						nd = creatNoeud(Tar,fg,fd);
						empile(&nd,size_arbre,&pa);

						i++;
					}else
						Erreur = 1;	
			car  = exp[i];
	}
	return (*((Arbre *)sommetPile(pa)));
}
float evalExpPostFixe(Arbre a){
 float vopG,vopD;
 char oper;

	if( estFeuille(a) )
		return donnee(a).nCar.operand;	
	else{
		vopG = evalExpPostFixe(filsG(a));
		vopD = evalExpPostFixe(filsD(a));
		oper = donnee(a).nCar.operation;
		return eval(oper,vopG,vopD);
	}
}
/*	<<<<<< PROGRAMME PRINCIPALE >>>>>>	*/
int main (void) {
 char exp[MAX_NB] ="((3.3+(16*2.22))-(4.06*(99.9-12.5)))";
 Arbre a;			
 
 a = transformExpArbre(exp);
 printf("parcoursPostFixee = ");
 parcourPostfixe(a);
 printf("\n");
 printf("%s = %g.\n",exp,evalExpPostFixe(a));
return 0;
}