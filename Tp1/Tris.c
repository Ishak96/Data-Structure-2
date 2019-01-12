#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define DIM 1000
#define VMAX 100000

typedef int TElement;

void Afficher_tab(int nbElt, TElement *tab){
	int i;

	for(i=0; i<nbElt; i++){
		printf("%i\t", tab[i]);
	}
	printf("\n");
}

void permutation(int l, int k, TElement *tab){
	TElement tmp;

	tmp = tab[l];
	tab[l] = tab[k];
	tab[k] = tmp;
}

int partitionner(int indinf, int indsup, TElement *tab){
	int indicePivot=indinf;
	TElement pivot=tab[indicePivot];
	int l=indinf;
	int k=indsup;

	while(l<=k){
		while(l<=k && tab[l]<=pivot){
			l=l+1;
		}
		while(l<=k && tab[k]>pivot)
		{
			k=k-1;
		}

		if(l<k)
		{
			permutation(l,k,tab);
			l=l+1;
			k=k-1;
		}
	}
	if(indicePivot!=k){
			permutation(k,indicePivot,tab);
	}
	return k;
}

void triRapide(int indinf, int indsup, TElement *tab){
	int indicePivot;
	if(indinf<indsup)
	{
		indicePivot=partitionner(indinf,indsup,tab);
		triRapide(indinf,indicePivot-1,tab);
		triRapide(indicePivot+1,indsup,tab);
	}
}

void fusioner_2_tab_trie(int n1, int n2, TElement *tab1, TElement *tab2, TElement *tab3, int indinf, int indsup){
	int i,j,k;

	//ajout d'un sentinelle
	tab1[n1]=VMAX;
	tab2[n2]=VMAX;

	//la fusion
	i=0;
	j=0;

	for (k=indinf; k<=indsup; k++)
	{
		if (tab1[i]<=tab2[j])
		{
			tab3[k]=tab1[i];
			i++;
		}
		else{
			tab3[k]=tab2[j];
			j++;
		}
	}
}

void fusioner(int indinf, int indsup, int indmil, TElement *tab){
	int i,k,n1,n2;
	TElement tab1[DIM];
	TElement tab2[DIM];

	//construction de tab1
	for(i=indinf; i<=indmil; i++)
	{
		tab1[i-indinf]=tab[i];
	}
	//construction de tab2
	for (i=indmil+1; i<=indsup; i++)
	{
		tab2[i-(indmil+1)]=tab[i];
	}

	n1=indmil-indinf+1;
	n2=indsup-(indmil+1)+1;

	fusioner_2_tab_trie(n1, n2, tab1, tab2, tab, indinf, indsup);
}

void triFusion(int indinf, int indsup, TElement *tab){
	int indmil;

	if (indinf<indsup)
	{
		/* Diviser */
		indmil=(indinf+indsup)/2;
		/*Régner*/
		triFusion(indinf,indmil,tab);
		triFusion(indmil+1,indsup,tab);
		/*Combiner*/
		fusioner(indinf,indsup,indmil,tab);
	}
}

void triInsertion(int nbElt, TElement *tab){
	int i,j;
	TElement carte;

	for(j=1; j<nbElt; j++){
		carte=tab[j];
		i=j-1;

		while(i>=0 && tab[i]>carte){
			tab[i+1]=tab[i];
			i=i-1;
		}
		tab[i+1]=carte;
	}
}

void creat_Tab_aleat(int nbElt, TElement *tab, TElement min, TElement max){
	int i;
	TElement nbAleat;

	srand(time(NULL));
	for (int i = 0; i < nbElt; ++i)
	{
		nbAleat=rand()%(max-min+1)+min;
		tab[i]=nbAleat;
	}
}

void creat_Tab_aleat_defav_fav(int nbElt, TElement *tab, TElement min, TElement max, int fav){
	int i;
	TElement nbAleat;

	nbAleat=rand()%(max-min+1)+min;
	tab[0]=nbAleat;

	srand(time(NULL));
	for (int i = 1; i < nbElt; ++i)
	{
		if (fav)
		{
			tab[i]=nbAleat;
			nbAleat=nbAleat+10;
		}
		else
		{
			tab[i]=nbAleat;
			nbAleat=nbAleat-10;
		}
	}
}

int creat_Tab_file (TElement *tab){
	FILE *fichier=NULL;
	char chaine[DIM] = "";
	int i,j,k,nbElt,m,indice;
	TElement elt;
	char numberChar[DIM],nbEltChar[DIM];

	fichier=fopen("valeurs.txt","r+");

    if (fichier!=NULL)
    {
        while (fgets(chaine, DIM, fichier)!=NULL)
        {
        	for (i = 0; i < DIM; ++i)
        	{
        		if (chaine[i])
        		{
        			if (chaine[i]=='N' && chaine[i+2]=='b')
        			{
        				for (j = i+1; j < DIM; ++j)
        				{
        					if (chaine[j]=='=')
        					{	
        						m=0;
        						for (k = j+1; k < DIM; ++k)
        						{
        							nbEltChar[m]=chaine[k];
        							m++;		
        						}
        						nbElt=atoi(nbEltChar);
        					}
        				}
        			}
        			if(chaine[i]=='=' && chaine[i-3]=='V')
        			{
        				k=0;
        				for (j = i+1; j < DIM; ++j)
        				{
        					numberChar[k]=chaine[j];
        					k++;
        				}
        				indice=chaine[i-1]-'0';
        				elt=atoi(numberChar);
        				tab[indice]=elt;
        			}
        		}
        	}
        }
    	fclose(fichier);
    }
    return nbElt;
}


void temps_exec_TriInsertion(){
	int i;
	TElement tab[DIM];
	FILE * fichier1;
	float temps;
 	clock_t t1,t2;

	fichier1=NULL;

	fichier1 = fopen("triFusion.txt", "w+");
	for (int i = 0; i < 300; i++)
	{
		creat_Tab_aleat(i,tab,100,200);
		t1=clock();
			triFusion(0,i+1,tab);
		t2=clock();
    	temps=(float)(t2-t1)/CLOCKS_PER_SEC;

		if (fichier1 != NULL)
		{
			fprintf(fichier1, "n=%d,m=%f\n", i, temps);
		}
	}
	for (int i = 0; i < 300; i++)
	{
		creat_Tab_aleat_defav_fav(i,tab,100,200,1);
		t1=clock();
			triFusion(0,i+1,tab);
		t2=clock();
    	temps=(float)(t2-t1)/CLOCKS_PER_SEC;

		if (fichier1 != NULL)
		{
			fprintf(fichier1, "n=%d,f=%f\n", i, temps);
		}
	}
	for (int i = 0; i < 300; i++)
	{
		creat_Tab_aleat_defav_fav(i,tab,100,200,0);
		t1=clock();
			triFusion(0,i+1,tab);
		t2=clock();
    	temps=(float)(t2-t1)/CLOCKS_PER_SEC;

		if (fichier1 != NULL)
		{
			fprintf(fichier1, "n=%d,d=%f\n", i, temps);
		}
	}
	fclose(fichier1);
}

int main(void)
{
	/* code */
	/*TElement tab1[DIM]={7,8,3,2,9,12,4}, n=7;
	TElement tab2[DIM];
	TElement tab3[DIM];
	int nbEltTab3;

	creat_Tab_aleat(n,tab2,100,200);
	nbEltTab3=creat_Tab_file (tab3);

	triInsertion(n,tab1);
	printf("Le tri par insertion creation du tableau normal\n");
	Afficher_tab(n,tab1);

	triFusion(0,n-1,tab2);
	printf("Le tri par fusion creation aléatoir du tableau\n");
	Afficher_tab(n,tab2);

	
	triRapide(0,nbEltTab3-1,tab3);	
	printf("Le tri Rapide creation du tableau 'depuis un fichier'\n");
	Afficher_tab(nbEltTab3,tab3);*/

	temps_exec_TriInsertion();
	
	return 0;
}