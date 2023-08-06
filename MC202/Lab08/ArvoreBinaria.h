#ifndef ARVOREBINARIA
#define ARVOREBINARIA

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

typedef struct _ArvoreBinaria {
  int info; /* informacao */
  struct _ArvoreBinaria *esq, *dir; /* subarvores esquerda e direita */
} ArvoreBinaria, NoArvoreBinaria;

//ADAPTEI O CODIGO DO PROFESSOR PARA CONSTRUIS ARVORE DE INTEIROS
int n_nos(NoArvoreBinaria *T);

void pre_ord(NoArvoreBinaria *T);

void pos_ord(NoArvoreBinaria *T);
                                                                        // <-- MINHA FUNCOES
void in_ord(NoArvoreBinaria *T);

int max_2(int n1, int n2);

void espelho(NoArvoreBinaria *T);

void output(NoArvoreBinaria *T);
//_______________________________________________________________________________^

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


#endif
