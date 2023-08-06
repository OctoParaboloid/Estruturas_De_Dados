#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>

#define BRANCO 0 /* O no nunca foi visitado (nunca entrou em Q) */
#define CINZA  1 /* O no ja foi visitado mas ainda nao foi processado */
#define PRETO  2 /* O no ja foi processado (ja saiu de Q) */





//*********************
//_____FILA__________
//*********************

typedef enum _bool {
  false, true
} bool;

typedef struct _fila {
    int ini, fim; // Posição inicial e final da fila
    int qtde; // Número de elementos na fila
    int tam_max; // Tamanho máximo na fila
    int *val; // Vetor com os valores
} Fila;


Fila *CriaFila(int tam_max);

/* Destroi a fila na memória */
void DestroiFila(Fila **Q);

/* Checa se a fila está vazia */
bool FilaVazia(Fila *Q);

/* Checa se a fila está cheia */
bool FilaCheia(Fila *Q);

bool InsereFila(Fila *Q, int elem);

/* Remove o elemento na frente da fila */
int RemoveFila(Fila *Q);

//************************* FIM FILA*********************
//************************* FIM FILA*********************
//************************* FIM FILA*********************



//************************* GRAFO *********************
//************************* GRAFO *********************
//************************* GRAFO *********************
//************************* GRAFO *********************
typedef struct _grafo
{
  int       n; /* numero de nos */
  int **m_adj; //matriz de adjacencia

  //Estrutura do grafo
  char *nome;
  int *pred;
  int *custo;
  int *rotulo;

} Grafo;

Grafo *cria_grafo(int n);

void destroi_grafo(Grafo *G);

// ************************** Grafo FIM**************


//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************

void DFS_visit_AZ(Grafo *G, int no_atual, int *cor); //percorre em ordem alfabetica


void PercursoProfundidade_AZ(Grafo *G, int raiz);


void DFS_visit_ZA(Grafo *G, int no_atual, int *cor); //percorre em ordem alfabetica inversa


void PercursoProfundidade_ZA(Grafo *G, int raiz); //percorre em ordem alfabetica inversa


void PercursoLargura(Grafo *G, int raiz);


void ImprimePred(Grafo *G);


void ImprimeCusto(Grafo *G);


//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************  FIM FIM FIM
//***************** Algoritmos Grafo *********************

#endif
