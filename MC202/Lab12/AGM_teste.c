#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>
#include <math.h>

#define BRANCO 0 /* O no nunca foi visitado (nunca entrou em Q) */
#define CINZA  1 /* O no ja foi visitado mas ainda nao foi processado */
#define PRETO  2 /* O no ja foi processado (ja saiu de Q) */









//*********************** HEAP **********************
//*********************** HEAP **********************
//*********************** HEAP **********************
typedef struct _no_grafo
{
    int i;
    int custo;
}NoGrafo;


typedef struct _Heap
{
    NoGrafo *vetor;
    int qtde;
    int tam_max;
}Heap;

Heap *cria_heap(int tam)
{
    Heap *novo_heap = (Heap *)calloc(1, sizeof(Heap));

    novo_heap->vetor = (NoGrafo *)calloc(tam, sizeof(NoGrafo));
    novo_heap->qtde = 0;
    novo_heap->tam_max = tam;

    return(novo_heap);
}

void troca(NoGrafo *v1, NoGrafo *v2)
{
    int aux_i = v1->i;
    int aux_custo = v1->custo;

    v1->i = v2->i;
    v1->custo = v2->custo;

    v2->i = aux_i;
    v2->custo = aux_custo;
}

void sobe_min_heap(Heap *h, int n)
{
    if (n != 0)
    {
        int pai = (n-1)/2;
        printf("comparando %d com %d\n", h->vetor[n].custo, h->vetor[pai].custo);
        if (h->vetor[n].custo < h->vetor[pai].custo)
        {
            printf("        subindo no heap: %d < %d\n", h->vetor[n].custo, h->vetor[pai].custo);
            troca(&(h->vetor[n]), &(h->vetor[pai]));
            sobe_min_heap(h, pai);
        }
    }
}

void desce_min_heap(Heap *h, int i)
{
    int menor = i;
    if ((2*i + 1 < h->qtde) && (h->vetor[2*i + 1].custo < h->vetor[menor].custo) )
        menor = 2*i + 1;
    if ((2*i + 2 < h->qtde) && (h->vetor[2*i + 2].custo < h->vetor[menor].custo) )
        menor = 2*i + 2;

    if (menor != i)
    {
        troca(&(h->vetor[menor]), &(h->vetor[i]));
        desce_min_heap(h, menor);
    }

}

void insere_min_heap(Heap *h, int i, int custo)
{
    if (h->qtde != h->tam_max)
    {
        printf("inserindo no:%c com custo:%d\n", (char)(65+i), custo);
        h->qtde++;

        h->vetor[h->qtde - 1].i = i;
        h->vetor[h->qtde - 1].custo = custo;

        sobe_min_heap(h, h->qtde - 1);
    }
}

void remove_min_heap(Heap *h)
{
    if (h->qtde > 0)
    {
    h->qtde--;
    //cliente *retorno = h->vetor_clientes[0];
    troca(&(h->vetor[0]), &(h->vetor[h->qtde]));
    desce_min_heap(h, 0);

	//return(retorno);
    }
    //return(NULL);
}

void destroi_heap(Heap *h)
{
    free(h->vetor);
    free(h);
}

//*********************** HEAP FIM **********************
//*********************** HEAP FIM **********************
//*********************** HEAP FIM **********************



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

Grafo *cria_grafo(int n)
{
    Grafo *novo_grafo = (Grafo *)calloc(1, sizeof(Grafo));

    novo_grafo->n = n;

    //matriz de adjacencia
    novo_grafo->m_adj = (int **)calloc(n, sizeof(int *)); //n linhas
    for (int i = 0; i < n; i++)
    {
        novo_grafo->m_adj[i] = (int *)calloc(n, sizeof(int)); //n colunas
    }

    novo_grafo->nome = (char *)calloc(n, sizeof(char));
    for (int i = 0; i < n; i++)
    {
        novo_grafo->nome[i] = (char)(65 + i);
    }

    novo_grafo->pred = (int *)calloc(n, sizeof(int));
    novo_grafo->custo = (int *)calloc(n, sizeof(int));
    novo_grafo->rotulo = (int *)calloc(n, sizeof(int));

    return(novo_grafo);
}


void destroi_grafo(Grafo *G)
{
    for (int i = 0; i < G->n; i++)
    {
        free(G->m_adj[i]);
    }
    free(G->m_adj);

    free(G->nome);
    free(G->pred);
    free(G->custo);
    free(G->rotulo);

    free(G);

    return;
}
// ************************** Grafo FIM**************
void  ArvoreGeradoraMinima(Grafo *G, int inicio)
{

    int *cor=(int *)calloc(G->n,sizeof(int));
    Heap *Q=cria_heap(19);

    /* Inicializacao */
    for (int i = 0; i < G->n; i++)
    {
        cor[i] = BRANCO;
        G->custo[i] = INT_MAX;
        G->pred[i] = -1;
    }
  G->custo[inicio] = 0; /* custo do caminho para a raiz */
  insere_min_heap(Q,inicio, 0);
  cor[inicio]=CINZA;

  /* Relaxacao e propagacao */

    while (Q->qtde > 0)
    {
        int u = Q->vetor[0].i;
        printf("\n");
        for (int l = 0 ; l < Q->qtde; l++) printf("%d, ", Q->vetor[l].custo);
        printf("\nvetor custos");
        for (int l = 0; l <G->n; l++) printf("%d, ", G->custo[l]);

        printf("\nsaiu do heap no %c com custo %d\n", G->nome[u], G->custo[u]);
        remove_min_heap(Q);
        cor[u]=PRETO;

        for (int i=0; i < G->n; i++)
        {
            if (u == i || G->m_adj[u][i] == 0) continue;
            int v = i;
            printf("... checando se %d=2 ou %d < %d\n", cor[v], G->custo[u], G->custo[i]);
            if ((cor[v]!=PRETO)&&(G->m_adj[u][i] < G->custo[i]))
            {
                int tmp = G->m_adj[u][i];
                printf("De %c pra %c, custo:%d\n", G->nome[u], G->nome[v], tmp);
                if (tmp < G->custo[v])
                {
                    printf("%d  < %d atualizando...\n", tmp, G->custo[v]);
                    G->custo[v] = tmp;
                    G->pred[v] = u;
                    if (cor[v]==BRANCO)
                    {
                        printf("inserindo no heap...\n");
                        insere_min_heap(Q, v, tmp);
                        cor[v]=CINZA;
                    } else
                    {
                        int k;
                        for (k = 0; k < Q->qtde; k++)
                        {
                            if (Q->vetor[k].i == v) break;
                        }
                        Q->vetor[k].custo = tmp;
                        sobe_min_heap(Q, k);
                    }
                }
            }
        }
    }
  free(cor);

  destroi_heap(Q);
}

void valor_agm(Grafo *G)
{
    int valor = 0;

    for (int i = 0; i < G->n; i++)
    {
        valor += G->custo[i];
    }
    printf("%d", valor);
}




//********************* MAIN****************************
//********************* MAIN****************************
//********************* MAIN****************************
//********************* MAIN****************************
void le_grafo(char *arquivo)
{
    FILE *f = fopen(arquivo, "r");

    int n;
    fscanf(f, "%d\n", &n);

    Grafo *G = cria_grafo(15);

    for(int i = 0; i < n; i++)
    {
        char no1, no2;
        int peso;
        fscanf(f, "%c %c %d\n", &no1, &no2, &peso);
        G->m_adj[no1-65][no2-65] = peso;
        G->m_adj[no2-65][no1-65] = peso;
    }
    ArvoreGeradoraMinima(G, 0);

    valor_agm(G);

    destroi_grafo(G);

    fclose(f);
}



int main()
{

    le_grafo("input.txt");


    return(0);
}
