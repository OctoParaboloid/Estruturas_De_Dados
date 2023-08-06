#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H
#include <stdio.h>
#include <stdlib.h>


typedef struct _cliente
{
    char sobrenome[50];
    int prioridade;
    int id_max, id_min;
}cliente;

typedef struct _Heap
{
    cliente **vetor_clientes;
    int qtde;
    int tam_max;
}Max_heap, Min_heap, Heap;

typedef struct _FilaPrio
{
    Max_heap *max_heap;
    Min_heap *min_heap;
    int qtde;
    int tam_max;
}fila_prioridade;


//PRIVADAS
cliente *cria_cliente(int prioridade, char *sobrenome);


Heap *cria_heap(int tam);


void troca(cliente **cl1, cliente **cl2);


int compara_sobrenome(char *nome1, char *nome2);  //1 se igual, 0 se diferente


int busca_max_heap(Heap *h, char *sobrenome);


	//MAX HEAP ~~~~~~~~~~~~
void sobe_max_heap(Heap *h, int n);


void desce_max_heap(Heap *h, int i);


void insere_max_heap(Heap *h, cliente *novo_cliente);


void remove_max_heap(Heap *h);


void remove_ID_max_heap(Heap *h, int id_max);

	//MAX HEAP ~~~~~~~~~~~~ FIM

    //MIN HEAP ~~~~~~~~~~~~
void sobe_min_heap(Heap *h, int n);


void desce_min_heap(Heap *h, int i);


void insere_min_heap(Heap *h, cliente *novo_cliente);


void remove_min_heap(Heap *h);


void remove_ID_min_heap(Heap *h, int id_min);

    //MIN HEAP ~~~~~~~~~~~~ FIM


void atualiza_max_heap(Heap *h, int id, int prioridade_nova);


void atualiza_min_heap(Heap *h, int id, int prioridade_nova);

//PRIVADAS FIM~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//CHAMADAS PELA MAIN ~~~~~~~~~~~~~~~~~~~~~~
fila_prioridade *cria_fila_prio(int tam);


void insere_cliente(fila_prioridade *fila, char *sobrenome, int prioridade_nova);


void busca_muda_cliente(fila_prioridade *f, char *sobrenome, int prioridade_nova);


void remove_prim_fila(fila_prioridade *fila);


void remove_ult_fila(fila_prioridade *fila);


void imprime_p_u(fila_prioridade *fila);


void destroi_heap(Heap *h);


void destroi_fila(fila_prioridade *fila);
#endif // FILAPRIORIDADE_H
