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


Fila *CriaFila(int tam_max)
{
    Fila *Q    = (Fila*) calloc(1, sizeof(Fila));
    Q->val     = (int*) calloc(tam_max, sizeof(int));
    Q->tam_max = tam_max;
    Q->qtde    = 0;
    Q->ini     = Q->fim = 0;

    return Q;
}

/* Destroi a fila na memória */
void DestroiFila(Fila **Q)
{
    Fila *Qaux = *Q;
    if (Qaux != NULL)
    {
        free(Qaux->val); // desaloca o vetor de int
        free(Qaux);
        *Q = NULL;
    }
}

/* Checa se a fila está vazia */
bool FilaVazia(Fila *Q)
{
    return (Q->qtde == 0);
}

/* Checa se a fila está cheia */
bool FilaCheia(Fila *Q)
{
    return (Q->qtde == Q->tam_max);
}


bool InsereFila(Fila *Q, int elem)
{
    if (FilaCheia(Q))
    {
        return false; // falha na insercao
    }
    else
    {
        Q->val[Q->fim] = elem;
        Q->fim = (Q->fim+1) % Q->tam_max;
        Q->qtde++;
        return true; // sucesso na insercao
    }
}

/* Remove o elemento na frente da fila */
int RemoveFila(Fila *Q)
{
    if (FilaVazia(Q))
    {
        return(-1); // falha na remocao
    }
    else
    {
        int res = Q->val[Q->ini];
        Q->ini = (Q->ini+1) % Q->tam_max;
        Q->qtde--;
        return(res); // sucesso na remocao
    }
}
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



//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************

void DFS_visit_AZ(Grafo *G, int no_atual, int *cor) //percorre em ordem alfabetica
{
    cor[no_atual] = CINZA;
    /* Visita os adjacentes */
    for (int v = 0; v < G->n; v++)
    {
        if (v == no_atual || G->m_adj[no_atual][v] == 0) continue;
        int adj = v;
        if (cor[adj] == BRANCO)
        {
            G->pred[adj]  = no_atual;
            G->custo[adj] = G->custo[no_atual] + 1;
            DFS_visit_AZ(G, adj, cor);
        }
    }
    cor[no_atual] = PRETO;
}

void PercursoProfundidade_AZ(Grafo *G, int raiz)
{
  /*Inicialização*/
    int *cor = (int *)calloc(G->n, sizeof(int));
    for (int i = 0; i < G->n; i++)
    {
        cor[i] = BRANCO;
        G->custo[i] = INT_MAX;
        G->pred[i] = -1;
    }

    /* Inicializa a raiz */
    G->custo[raiz] = 0;
    DFS_visit_AZ(G, raiz, cor);

    for (int i = 0; i < G->n; i++)
    {
        if (cor[i] == BRANCO)
        {
            G->custo[raiz] = 0;
            DFS_visit_AZ(G, i, cor);
        }
    }
    free(cor);
}

void DFS_visit_ZA(Grafo *G, int no_atual, int *cor) //percorre em ordem alfabetica inversa
{
    cor[no_atual] = CINZA;
    /* Visita os adjacentes */
    for (int v = G->n - 1; v >= 0; v--)
    {
        if (v == no_atual || G->m_adj[no_atual][v] == 0) continue;
        int adj = v;
        if (cor[adj] == BRANCO)
        {
            G->pred[adj]  = no_atual;
            G->custo[adj] = G->custo[no_atual] + 1;
            DFS_visit_ZA(G, adj, cor);
        }
    }
    cor[no_atual] = PRETO;
}

void PercursoProfundidade_ZA(Grafo *G, int raiz) //percorre em ordem alfabetica inversa
{
  /*Inicialização*/
    int *cor = (int *)calloc(G->n, sizeof(int));
    for (int i = 0; i < G->n; i++)
    {
        cor[i] = BRANCO;
        G->custo[i] = INT_MAX;
        G->pred[i] = -1;
    }

    /* Inicializa a raiz */
    G->custo[raiz] = 0;
    DFS_visit_ZA(G, raiz, cor);

    for (int i = G->n - 1; i >= 0; i--)
    {
        if (cor[i] == BRANCO)
        {
            G->custo[raiz] = 0;
            DFS_visit_ZA(G, i, cor);
        }
    }
    free(cor);
}

void PercursoLargura(Grafo *G, int raiz)
{
    //inicializacao
    Fila *Q=CriaFila(G->n);
    int *cor = (int *)calloc(G->n, sizeof(int));
    for (int i = 0; i < G->n; i++)
    {
        cor[i] = BRANCO;
        G->custo[i] = INT_MAX;
        G->pred[i] = -1;
    }


    //inicia raiz
    cor[raiz] = CINZA;
    G->custo[raiz] = 0;
    InsereFila(Q, raiz);

    //percurso
    while (!FilaVazia(Q))
    {
        int no_atual = RemoveFila(Q);
        cor[no_atual] = PRETO;

        for (int i = 0; i < G->n; i++)
        {
            if (i == no_atual || G->m_adj[no_atual][i] == 0) continue;

            if (cor[i] == BRANCO)
            {
                G->pred[i] = no_atual;
                G->custo[i] = G->custo[no_atual] + 1;
                cor[i] = CINZA;
                InsereFila(Q, i);
            }
        }
    }


    //libera
    DestroiFila(&Q);
    free(cor);
}

void ImprimePred(Grafo *G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (G->pred[i] == -1)
        {
            printf("NIL ");
        }
        else
        {
            printf("%c ", G->nome[G->pred[i]]);
        }
    }
}

void ImprimeCusto(Grafo *G)
{
    for (int i = 0; i < G->n; i++)
    {
        if (G->custo[i] == INT_MAX)
        {
            printf("inf ");
        }
        else
        {
            printf("%d ", G->custo[i]);
        }

    }
}

//***************** Algoritmos Grafo *********************
//***************** Algoritmos Grafo *********************  FIM FIM FIM
//***************** Algoritmos Grafo *********************



//                 ************************************ MAIN
//                 ************************************
//                 ************************************
//                 ************************************
//                 ************************************ MAIN
//                 ************************************
//                 ************************************
//                 ************************************
//                 ************************************
//                 ************************************
//funcao principal, registra o grafo e realiza os percursos
void le_grafo(char *arquivo)
{
    FILE *f = fopen(arquivo, "r");

    int n;
    fscanf(f, "%d\n", &n);

    Grafo *G = cria_grafo(n);

    for(int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
            {
                fscanf(f, "%d\n", &G->m_adj[i][j]);
            }
            else
            {
                fscanf(f, "%d ", &G->m_adj[i][j]);
            }
        }
    }


    PercursoLargura(G, 1);
    ImprimePred(G);
    printf("\n");

    ImprimeCusto(G);
    printf("\n");

    PercursoProfundidade_AZ(G, 1);
    ImprimePred(G);
    printf("\n");

    PercursoProfundidade_ZA(G, 1);
    ImprimePred(G);


    destroi_grafo(G);
}



int main()
{

    le_grafo("input1.txt");


    return(0);
}
