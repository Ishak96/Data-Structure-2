#include<GL/gl.h>
#include<GL/glut.h>
#include <GL/glu.h>
#include<stdio.h>

#define DIM 100000

typedef struct
{
  int x;
  int y;
}Point;

typedef struct 
{
  float r;
  float g;
  float b;
}RGB;

RGB rouge = {1.0,0.0,0.0};
RGB vert = {0.0,1.0,0.0};
RGB bleu ={0.0,0.0,1.0};
RGB blanc ={1.0,1.0,1.0};

void drawPoint(int xa, int ya, RGB couleur, float width){
  glPointSize(width);
  glColor3f(couleur.r, couleur.g, couleur.b);
  glBegin(GL_POINTS);
    glVertex2i(xa+250, ya+250);
  glEnd();
}

void drawLine(int xa, int ya, int xb, int yb, RGB couleur, float width){
  glLineWidth(width);
  glColor3f(couleur.r, couleur.g, couleur.b);
  glBegin(GL_LINES);
    glVertex2i(xa+250, ya+250);
    glVertex2i(xb+250, yb+250);
  glEnd();
}

void display (void){
  Point p1={0,250};
  Point p2={250,0};

  drawLine(p1.x, p1.y, p1.x, -p1.y, blanc, 0.5);
  drawLine(p2.x, p2.y, -p2.x, p2.y, blanc, 0.5);
glFlush();
}

void init (void){

  glColor3f(0.0,0.0,0.0);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glOrtho(230.0,500.0,230.0,500.0,100.0,-100.0);
}

void recupereDonnes(Point *tabFav, int *n1, Point *tabDeFav, int *n2, Point *tabMoyDesCas, int *n3){
  FILE *fichier;
  char chaine[DIM]="";
  int i,j,p,l,k,m,nbElt,e1,e2,e3,exp;
  float temp;
  Point po;

  fichier=NULL;
  e1=e2=e3=0;
  exp=1000000;

  fichier=fopen("triRapide.txt","r+");
  if (fichier != NULL)
  {
    while(fgets(chaine, DIM, fichier))
    {
      char nbEltChar[DIM]="";
      char tempsChar[DIM]="";
      for (i = 0; i < DIM; i++)
      {
        if (chaine[i])
        {
          if (chaine[i]=='n')
          {
            p=i+2;
            m=0;
            while(chaine[p]!=',')
            {
              nbEltChar[m]=chaine[p];
              m++;
              p++;
            }
            nbElt=atoi(nbEltChar);
          }
          if (chaine[i]==',')
          {
            k=i+3;
            l=0;
            while(chaine[k])
            {
              tempsChar[l]=chaine[k];
              l++;
              k++;
            }
            temp=atof(tempsChar);
            po.x=nbElt; 
            po.y=(int)((temp)*exp);
            if (chaine[i+1]=='f')
            {
              tabFav[e1]=po;
              e1++;
            }
            else
            {
              if (chaine[i+1]=='d')
              {
                tabDeFav[e2]=po;
                e2++;
              }
              else
              {
                tabMoyDesCas[e3]=po;
                (e3)++;
              }
            }
          }
        }
      }
    }
    fclose(fichier); 
  }
  *n1=e1;
  *n2=e2;
  *n3=e3;
}

void Afficher_tab(int nbElt, Point *tab){
  int i;

  for(i=0; i<nbElt; i++){
    printf("(%d,%d)\t", tab[i].x, tab[i].y);
  }
  printf("\n");
}

void triInsertion(int nbElt, Point *tab){
  int i,j;
  Point carte;

  for(j=1; j<nbElt; j++){
    carte=tab[j];
    i=j-1;

    while(i>=0 && tab[i].y>carte.y){
      tab[i+1]=tab[i];
      i=i-1;
    }
    tab[i+1]=carte;
  }
}

void drawGraph(Point *tab, int n, RGB couleur){
  int i;
  int xa,ya;

  triInsertion(n, tab);
  for (i=0; i<n; i++)
  {
    xa=tab[i].x;
    ya=tab[i].y;
    drawPoint(xa, ya, couleur, 4);
  }
}

int main(int argc, char** argv){

 Point tabFav[DIM], tabDeFav[DIM], tabMoyDesCas[DIM];
 int n1,n2,n3;

 n1=n2=n3=0;

 glutInit(&argc,argv);

 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

 glutInitWindowSize(500,500);

 glutInitWindowPosition(200,200);

 glutCreateWindow("Tri Rapide");
 init();

 glutDisplayFunc(display);

 recupereDonnes(tabFav, &n1, tabDeFav, &n2, tabMoyDesCas, &n3);
 drawGraph(tabMoyDesCas, n3, vert);
 drawGraph(tabFav, n1, bleu);
 drawGraph(tabDeFav, n2, rouge);

 glutMainLoop();

return 0;
}
