#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<malloc.h>
#include <math.h>

typedef struct 
{
	double coef;
	int degre;
}Monome;

typedef struct cellule
{
	Monome monMonome;
	struct cellule *suiv;
	struct cellule *pred;
}*MonomeCellule;

typedef struct 
{
	MonomeCellule tetePoly;
	MonomeCellule queuePoly;
	int taille;
}Polynome;

/*Fonctions de base*/

double coefMonome(Monome m){
	return m.coef;
}

int degreMonome(Monome m){
	return m.degre;
}

int equalsMonome(Monome m1, Monome m2){
	return((coefMonome(m1)==coefMonome(m2))&&(degreMonome(m1)==degreMonome(m2)));
}

Monome MonomeCourant(Polynome p){
	return (p.tetePoly)->monMonome;
}

MonomeCellule MonomeSuivant(MonomeCellule mC){
	return mC->suiv;
}

MonomeCellule MonomePrecedent(MonomeCellule mC){
	return mC->pred;
}

int videMonomeCellule(MonomeCellule mC){
	return mC->suiv==NULL && mC->pred==NULL;
}

Polynome initPolynome(){
	Polynome p;

	p.tetePoly=NULL;
	p.queuePoly=NULL;
	p.taille=0;

	return p;
}

int videPolynome(Polynome p){
	return p.tetePoly==NULL;
}

MonomeCellule initMonomeCellule(){
	MonomeCellule mc;

	mc->suiv=NULL;
	mc->pred=NULL;

	return mc;
}

void afficher_Poly(Polynome p){
	for(int i=0; i<p.taille; i++)
	{
		if (degreMonome(MonomeCourant(p))!=0)
		{
			if (coefMonome(MonomeCourant(p))>0)
			{
				printf("+%2.fX^%d  ",coefMonome(MonomeCourant(p)),degreMonome(MonomeCourant(p)));
			}
			else
			{
				printf("%2.fX^%d  ",coefMonome(MonomeCourant(p)),degreMonome(MonomeCourant(p)));
			}
		}
		else
		{
			printf("%2.f  ",coefMonome(MonomeCourant(p)));
		}
		p.tetePoly=(p.tetePoly)->suiv;
	}
	printf("\n");
}

MonomeCellule creatMonom(Monome m){
	MonomeCellule mC;

	mC=(MonomeCellule) malloc (sizeof(struct cellule));
	mC->monMonome=m;

	return mC;
}

void inserTeteMon(Monome m, MonomeCellule *mon){
	MonomeCellule mC;

	mC=creatMonom(m);

	if (videMonomeCellule(*mon))
	{
		mC->suiv=NULL;
		mC->pred=NULL;
		(*mon)=mC;
	}
	else
	{
		mC->pred=NULL;
		mC->suiv=*mon;
		(*mon)->pred=mC;
	}
}

void suppTeteMon(MonomeCellule *mon){
	MonomeCellule pt,spt,cel;

	spt=MonomeSuivant(*mon);
	cel=*mon;

	if (videMonomeCellule(spt))
	{
		*mon=NULL;
	}
	else
	{
		spt->pred=NULL;
		*mon=spt;
	}
	free(cel);
}

void inserTetePoly(Monome m, Polynome *p){
	MonomeCellule mC;

	mC=creatMonom(m);

	if (videPolynome(*p))
	{
		mC->suiv=NULL;
		mC->pred=NULL;
		p->tetePoly=mC;
		p->queuePoly=mC;
	}
	else
	{
		mC->pred=NULL;
		mC->suiv=p->tetePoly;
		(p->tetePoly)->pred=mC;
		p->tetePoly=mC;
	}
	p->taille=p->taille+1;
}

void suppTetePoly(Polynome *p){
	MonomeCellule pt,spt,cel;

	pt=p->tetePoly;
	spt=MonomeSuivant(pt);
	cel=pt;
	if (spt!=NULL)
	{
		if (videMonomeCellule(spt))
		{
			p->queuePoly=NULL;
		}
		else
		{
			spt->pred=NULL;
			p->tetePoly=spt;
		}
	}
	p->taille=p->taille-1;
	free(cel);
}

void suppQueuePoly(Polynome *p){
	MonomeCellule ql,pql,cel;

	ql=p->queuePoly;
	pql=MonomePrecedent(ql);
	cel=ql;

	if (videMonomeCellule(pql))
	{
		p->tetePoly=NULL;
	}
	else
	{
		pql->suiv=NULL;
		p->queuePoly=pql;
	}
	p->taille=p->taille-1;
	free(cel);
}

void inserQueuePoly(Monome m, Polynome *p){
	MonomeCellule mC;

	mC=creatMonom(m);

	if (videPolynome(*p))
	{
		mC->suiv=NULL;
		mC->pred=NULL;
		p->tetePoly=mC;
		p->queuePoly=mC;
	}
	else
	{
		mC->suiv=NULL;
		mC->pred=p->queuePoly;
		(p->queuePoly)->suiv=mC;
		p->queuePoly=mC;
	}
	p->taille=p->taille+1;
}

MonomeCellule rechMonPoly(Monome mon , Polynome p){
	MonomeCellule mt,mq,rechMon;

	mt=p.tetePoly;
	mq=p.queuePoly;
	rechMon=NULL;

	while(degreMonome(mon)>degreMonome((mt->monMonome)) && degreMonome(mon)<degreMonome((mq->monMonome)))
	{
		mt=MonomeSuivant(mt);
		mq=MonomePrecedent(mq);
	}

	if (equalsMonome(mon,mt->monMonome))
	{
		rechMon=mt;
	}
	else
	{
		if (equalsMonome(mon,mq->monMonome))
		{
			rechMon=mq;
		}
	}

	return rechMon;
}

void inserMonPoly(Monome m, Polynome *p){
	MonomeCellule mt,mq,pmt,smq;
	MonomeCellule mC;
	float cp;

	if (videPolynome(*p) || degreMonome(MonomeCourant(*p))>=degreMonome(m))
	{
		if (videPolynome(*p))
		{
			inserTetePoly(m,p);
		}
		else
		{
			if (degreMonome(MonomeCourant(*p))==degreMonome(m))
			{
				cp=((p->tetePoly)->monMonome).coef+m.coef;
				if (cp==0)
				{
					suppTetePoly(p);
				}
				else
				{
					((p->tetePoly)->monMonome).coef=cp;
				}
			}
			else
			{
				inserTetePoly(m,p);
			}
		}
	}
	else
	{
		if (degreMonome((p->queuePoly)->monMonome)<degreMonome(m))
		{
			inserQueuePoly(m,p);
		}
		else
		{
			mt=p->tetePoly;
			mq=p->queuePoly;

			while(degreMonome(m)>degreMonome((mt->monMonome)) && degreMonome(m)<degreMonome((mq->monMonome)))
			{
				mt=MonomeSuivant(mt);
				mq=MonomePrecedent(mq);
			}
			mC=creatMonom(m);

			if (degreMonome(m)<=degreMonome((mt->monMonome)))
			{
				if (degreMonome(m)==degreMonome((mt->monMonome)))
				{
					cp=(mt->monMonome).coef+m.coef;
					if (cp==0)
					{
						suppTeteMon(&mt);
						p->taille=p->taille-1;
					}
					else
					{
						(mt->monMonome).coef=cp;
					}
				}
				else
				{
					pmt=mt->pred;
					mC->suiv=mt;
					mC->pred=pmt;
					mt->pred=mC;
					pmt->suiv=mC;
					p->taille=p->taille+1;
				}
			}
			else
			{
				if (degreMonome(m)==degreMonome((mq->monMonome)))
				{
					cp=(mq->monMonome).coef+m.coef;
					if (cp==0)
					{
						suppTeteMon(&mq);
						p->taille=p->taille-1;
					}
					else
					{
						(mq->monMonome).coef=cp;
					}
				}
				else
				{
					smq=mq->suiv;
					mC->suiv=smq;
					mC->pred=mq;
					smq->pred=mC;
					mq->suiv=mC;
					p->taille=p->taille+1;
				}
			}
		}
	}
}

void delPolynome(Polynome *p){
	int taille;
	taille=p->taille;
	for (int i = 0; i<taille; i++)
	{
		suppTetePoly(p);
	}
}

void suppIMonPoly(Monome mon, Polynome *p){
	MonomeCellule mSup,mPred,mSuiv;

	mSup=rechMonPoly(mon,*p);
	if (mSup!=NULL)
	{
		if ((mSup)->suiv==NULL)
		{
			suppQueuePoly(p);
		}
		else
		{
			if ((mSup)->pred==NULL)
			{
				suppTetePoly(p);
			}
			else
			{
				mPred=(mSup)->pred;
				mSuiv=(mSup)->suiv;

				mPred->suiv=mSuiv;
				mSuiv->pred=mPred;
				p->taille--;

				free(mSup);
				mSup=NULL;
			}
		}
	}
}

float maxCoef(Polynome p){
	MonomeCellule mt,mq,rechMon;
	float maxCoefq,maxCoeft,maxCoef;

	mt=p.tetePoly;
	mq=p.queuePoly;

	maxCoefq=(mq->monMonome).coef;
	maxCoeft=(mt->monMonome).coef;

	while(degreMonome((mq->monMonome))>degreMonome((mt->monMonome)))
	{
		mt=MonomeSuivant(mt);
		mq=MonomePrecedent(mq);

		if ((mt->monMonome).coef>maxCoeft)
		{
			maxCoeft=(mt->monMonome).coef;
		}

		if ((mq->monMonome).coef>maxCoefq)
		{
			maxCoefq=(mq->monMonome).coef;
		}
	}
	maxCoef=maxCoefq;

	if (maxCoef<maxCoeft)
	{
		maxCoef=maxCoeft;
	}
	return maxCoef;
}

float sommeCoef(Polynome p){
	MonomeCellule mt,mq,rechMon;
	float somCoefq,somCoeft;

	somCoeft=somCoefq=0;
	mt=p.tetePoly;
	mq=p.queuePoly;

	while(degreMonome(mt->monMonome)<degreMonome(mq->monMonome))
	{
		somCoeft=somCoeft+(mt->monMonome).coef;
		somCoefq=somCoefq+(mq->monMonome).coef;

		mt=MonomeSuivant(mt);
		mq=MonomePrecedent(mq);
	}

	if (degreMonome(mt->monMonome)==degreMonome(mq->monMonome))
	{
		somCoefq=somCoefq+(mq->monMonome).coef;
	}
	return somCoefq+somCoeft;
}

Polynome sommePolynome(Polynome p1, Polynome p2){
	Polynome ps;
	float coef;
	MonomeCellule mtp1,mqp1,mtp2,mqp2;
	Monome mon;

	ps=initPolynome();
	
	mtp1=p1.tetePoly;
	mqp1=p1.queuePoly;
	mtp2=p2.tetePoly;
	mqp2=p2.queuePoly;

	while(degreMonome(mtp1->monMonome)<degreMonome(mqp1->monMonome))
	{
		inserMonPoly(mtp1->monMonome,&ps);
		inserMonPoly(mqp1->monMonome,&ps);
		mtp1=mtp1->suiv;
		mqp1=mqp1->pred;
	}
	if (degreMonome(mtp1->monMonome)==degreMonome(mqp1->monMonome))
	{
		inserMonPoly(mtp1->monMonome,&ps);
	}

	while(degreMonome(mtp2->monMonome)<degreMonome(mqp2->monMonome))
	{
		inserMonPoly(mtp2->monMonome,&ps);
		inserMonPoly(mqp2->monMonome,&ps);
		mtp2=mtp2->suiv;
		mqp2=mqp2->pred;
	}
	if (degreMonome(mtp2->monMonome)==degreMonome(mqp2->monMonome))
	{
		inserMonPoly(mtp2->monMonome,&ps);
	}	

	return ps;
}

Polynome derivPoly(Polynome p){
	Polynome dp;
	MonomeCellule mtp,mqp;
	Monome mt,mq;

	dp=initPolynome();
	mtp=p.tetePoly;
	mqp=p.queuePoly;

	while(degreMonome(mtp->monMonome)<degreMonome(mqp->monMonome))
	{
		if (degreMonome(mtp->monMonome)==0)
		{
			mtp=mtp->suiv;
		}
		else
		{
			mt.coef=coefMonome(mtp->monMonome)*degreMonome(mtp->monMonome);
			mt.degre=degreMonome(mtp->monMonome)-1;

			mq.coef=coefMonome(mqp->monMonome)*degreMonome(mqp->monMonome);
			mq.degre=degreMonome(mqp->monMonome)-1;

			inserMonPoly(mt,&dp);
			inserMonPoly(mq,&dp);

			mtp=mtp->suiv;
			mqp=mqp->pred;	
		}
	}
	if (degreMonome(mtp->monMonome)==degreMonome(mqp->monMonome))
	{
		mt.coef=coefMonome(mtp->monMonome)*degreMonome(mtp->monMonome);
		mt.degre=degreMonome(mtp->monMonome)-1;

		inserMonPoly(mt,&dp);
	}

	return dp;
}

Polynome gener_Poly(int nbMonome, int degreMax){
	Monome mn;
	Polynome ps;
	int degre,nbal1,nbal2,nbal3;
	float coef;

	ps=initPolynome();

	for (int i = 0; i < nbMonome; i++)
	{
		nbal1=rand()%(degreMax+1);
		nbal2=rand()%2;
		if (nbal2==1 && nbal1!=0)
		{
			nbal3=(rand()%(20-10+1)+10)/nbal1;	
		}
		else
		{
			nbal3=nbal1-(rand()%(20-10+1)+10);
		}
		mn.degre=nbal1;
		mn.coef=nbal3;

		inserMonPoly(mn,&ps);
	}

	return ps;
}

/*programme principale*/
int main (void) {
	srand(time(NULL));

	Polynome p1,p2,ps,dp;

	p1=gener_Poly(10,10);
	p2=gener_Poly(5,5);

	printf("p1(X)=");
	afficher_Poly(p1);
	printf("p2(X)=");
	afficher_Poly(p2);

	printf("le plus grand coefficient du polynome 2 est : %f\n", maxCoef(p2));
	printf("la somme des coefficient du polynome 2 est : %f\n", sommeCoef(p2));

	ps=sommePolynome(p1,p2);

	printf("la somme des deux polynomes ps(X)=");
	afficher_Poly(ps);

	dp=derivPoly(ps);

	printf("la deriver de la somme dp(X)=");
	afficher_Poly(dp);

	printf("la deriver second de la somme d2p(X)=");
	afficher_Poly(derivPoly(dp));

return 0;
}