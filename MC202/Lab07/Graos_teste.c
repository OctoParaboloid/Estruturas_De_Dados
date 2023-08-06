#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
//#include "ArvoreBinaria.c"

/* Constrói uma árvore binária a partir de dois percursos dados.

   gcc ConstroiArvoreBinaria.c -o ConstroiArvoreBinaria

*/


/*Reaproveitei o código do professor ArvoreBinaria.c e ArvoreBinaria.h*/


/*fiz apenas as funcoes max_2(), max_3() e SomaMax() e le_e_constroi()*/
                                            /* ________________*/
typedef struct _ArvoreBinaria {
  int info; /* informacao */
  struct _ArvoreBinaria *esq, *dir; /* subarvores esquerda e direita */
} ArvoreBinaria, NoArvoreBinaria;


int int_arraylen(int *v);

void NumeroNosEsquerdaDireita(int *sim, int raiz, int *ne, int *nd, int n);
void NosEsquerdaDireitaSim(int *sim, int ne, int nd, int **esq_sim, int **dir_sim);
void NosEsquerdaDireitaPos(int *pos, int ne, int nd, int **esq_pos, int **dir_pos);

/* Cria no de arvore binaria com subarvores esquerda e direita */

NoArvoreBinaria *CriaNoArvoreBinaria(ArvoreBinaria *esq, ArvoreBinaria *dir, int info);

/* Constroi arvore binaria a partir de strings de tamanho n com os
   percursos em ordem simetria e pos-ordem */

ArvoreBinaria *ConstroiArvoreBinariaSimPos(int *sim, int *pos, int n);

/* Retorna a altura de uma arvore binaria */

int Altura(ArvoreBinaria *T);

/* Imprime uma arvore binaria rotacionada de 90 graus */

void ImprimeArvoreBinaria(ArvoreBinaria *T, int h, int altura);

/* Percursos em profundidade */

void VisitaPreOrdem(ArvoreBinaria *T, char **s);
void VisitaPosOrdem(ArvoreBinaria *T, char **s);
void VisitaOrdemSimetrica(ArvoreBinaria *T, char **s);

/* Destroi Arvore Binaria */

void DestroiArvoreBinaria(ArvoreBinaria **T);

/* Exercicios: Visite os nos em largura com auxilio de uma fila,
   construa a arvore a partir de outras combinacoes de dois percursos,
   e apartir da notacao parentetica. Imprima a arvore em notacao
   parentetica. */

void BuscaAnteriorSimetrica(ArvoreBinaria *T, NoArvoreBinaria **no_ant, int info, char *achou);
                                                                                                /*HEADER*/


int int_arraylen(int *v)
{
    int q = 0;

    while (v[q])
    {
        q++;
    }
    return(q);
}

void NumeroNosEsquerdaDireita(int *sim, int raiz, int *ne, int *nd, int n)
{
  int i;
                                    printf("%d\n", raiz);
  *ne = *nd = i = 0;
  while (sim[i]!=raiz){
    i++;
  }
  (*ne) = i;
  (*nd) = n - (*ne) - 1;
}

void NosEsquerdaDireitaSim(int *sim, int ne, int nd, int **esq_sim, int **dir_sim)
{
  int i, j;

  /* Copia nos da subarvore esquerda */

  if (ne > 0){
    *esq_sim = (int *)calloc(ne,sizeof(int));
    for (i=0; i < ne; i++)
      (*esq_sim)[i] = sim[i];
  }else{
    *esq_sim = NULL;
  }

  /* Copia nos da subarvore direita */

  if (nd > 0) {
    *dir_sim = (int *)calloc(nd,sizeof(int));
    for (i=0, j=ne+1; i < nd; i++,j++)
      (*dir_sim)[i] = sim[j];
  } else {
    *dir_sim = NULL;
  }
}

void NosEsquerdaDireitaPos(int *pos, int ne, int nd, int **esq_pos, int **dir_pos)
{
  int i, j;

  /* Copia nos da subarvore esquerda */

  if (ne > 0){
    *esq_pos = (int *)calloc(ne,sizeof(int));
    for (i=0; i < ne; i++)
      (*esq_pos)[i] = pos[i];
  }else{
    *esq_pos = NULL;
  }

  /* Copia nos da subarvore direita */

  if (nd > 0) {
    *dir_pos = (int *)calloc(nd,sizeof(int));
    for (i=0, j=ne; i < nd; i++,j++)
      (*dir_pos)[i] = pos[j];
  } else {
    *dir_pos = NULL;
  }
}

/* --------------------------- Publicas -------------------------------------- */

/* Cria no de arvore binaria com subarvores esquerda e direita */

NoArvoreBinaria *CriaNoArvoreBinaria(ArvoreBinaria *esq, ArvoreBinaria *dir, int info)
{
  NoArvoreBinaria *p = (NoArvoreBinaria *)calloc(1,sizeof(NoArvoreBinaria));
  p->esq   = esq;
  p->dir   = dir;
  p->info  = info;
  return p;
}

/* Constroi arvore binaria a partir de strings de tamanho n com os
   percursos em ordem simetria e pos-ordem */

ArvoreBinaria *ConstroiArvoreBinariaSimPos(int *sim, int *pos, int n)
{
  int *esq_sim=NULL,*dir_sim=NULL,*esq_pos=NULL,*dir_pos=NULL;
  int   ne, nd;
  NoArvoreBinaria *p=NULL, *esq=NULL, *dir=NULL;

                                                                    printf("constroi 1\n");
  if (n == 1) {
    p = CriaNoArvoreBinaria(NULL,NULL,sim[0]);
  } else { /* n > 1 */
    NumeroNosEsquerdaDireita(sim,pos[n-1],&ne,&nd, n);              printf("  %d %d\n", ne, nd);
    NosEsquerdaDireitaSim(sim,ne,nd,&esq_sim,&dir_sim);
    NosEsquerdaDireitaPos(pos,ne,nd,&esq_pos,&dir_pos);

    if (esq_sim != NULL)
      esq = ConstroiArvoreBinariaSimPos(esq_sim, esq_pos, ne);

    if (dir_sim != NULL)
      dir = ConstroiArvoreBinariaSimPos(dir_sim, dir_pos, nd);

    p = CriaNoArvoreBinaria(esq,dir,pos[n-1]);
  }

  return(p);
}



void ImprimeArvoreBinaria(ArvoreBinaria *T, int h, int altura)
{
  int i;

  if (T != NULL) {
    ImprimeArvoreBinaria(T->dir, h+1, altura);
    for (i=0; i < h; i++)
      printf("   ");
    printf("%c",T->info);
    for (i=0; i < altura-h; i++)
      printf("---");
    printf("\n");
    ImprimeArvoreBinaria(T->esq, h+1,altura);
  }
}

void VisitaPreOrdem(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
    VisitaPreOrdem(T->esq, s);
    VisitaPreOrdem(T->dir, s);
  }
}

void VisitaOrdemSimetrica(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    VisitaOrdemSimetrica(T->esq, s);
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
    VisitaOrdemSimetrica(T->dir, s);
  }
}

void VisitaPosOrdem(ArvoreBinaria *T, char **s)
{
  if (T != NULL) {
    VisitaPosOrdem(T->esq, s);
    VisitaPosOrdem(T->dir, s);
    sprintf(*s,"%c ",T->info);
    (*s) = (*s) + strlen(*s);
  }
}


void DestroiArvoreBinaria(ArvoreBinaria **T)
{
  NoArvoreBinaria *p=*T;

  if (p != NULL){
    DestroiArvoreBinaria(&(p->esq));
    DestroiArvoreBinaria(&(p->dir));
    free(p);
    *T = NULL;
  }
}

void BuscaAnteriorSimetrica(ArvoreBinaria *T, NoArvoreBinaria **no_ant, int info, char *achou)
{
  if ((T != NULL)&&(!(*achou))){
    BuscaAnteriorSimetrica(T->esq,no_ant,info,achou);
    if (!(*achou)){
      if (T->info != info){
	(*no_ant) = T;
	BuscaAnteriorSimetrica(T->dir,no_ant,info,achou);
      } else {
	if (*no_ant != NULL)
	  (*achou)=1;
      }
    }
  }
}






 /*________________________________________*/
int max_2(int n1, int n2)
{
    if (n1 < n2) return(n2);
    return(n1);
}
int max_3(int n1, int n2, int n3)
{
    int max = max_2(n1, n2);
    if (n3 > max) return(n3);
    return(max);
}

int *SomaMax(ArvoreBinaria *T)
{

    int *Sm_Pm = (int *)calloc(2, sizeof(int));

    if (T == NULL)
    {
        Sm_Pm[0] = 0;
        Sm_Pm[1] = 0;
        return(Sm_Pm);
    }

    int *SP_esq = SomaMax(T->esq);
    int *SP_dir = SomaMax(T->dir);

    Sm_Pm[0] = max_3(SP_esq[0], SP_dir[0], T->info+SP_esq[0]+SP_dir[0]);
    Sm_Pm[1] = max_3(T->info+SP_esq[1], T->info+SP_dir[1], 0);

    return(Sm_Pm);
}
                                            /* ________________*/

ArvoreBinaria *le_e_constroi(char *nomearq)
{
    FILE *f = fopen(nomearq, "r");

    int n;
    fscanf(f, "%d\n", &n);
                                                    printf("aqui1\n");

    int **SimPos = (int **)calloc(2, sizeof(int *));

    SimPos[0] = (int *)calloc(n, sizeof(int));
    SimPos[1] = (int *)calloc(n, sizeof(int));
    int j;
                                                    printf("aqui2\n");
    for (int i = 0; i < 2; i++)
    {                                               printf("aqui3\n");
        for ( j = 0; j < n; j++)
        {
            fscanf(f, "%d ", &SimPos[i][j]);
        }

        fscanf(f, "\n");

    }
                                                    printf("aqui4\n");
    for (int i = 0; i < n; i++)printf("%d ", SimPos[0][i]);
    ArvoreBinaria *T = ConstroiArvoreBinariaSimPos(SimPos[0], SimPos[1], n);
                                                    printf("aqui5\n");
    fclose(f);
    return(T);
}

int main()
{
  ArvoreBinaria *T=NULL;


  T = le_e_constroi("graos_teste.txt");

  /* ________________*/
  printf("%d", SomaMax(T)[0]);
  /* ________________*/

  DestroiArvoreBinaria(&T);

  return(0);
}
