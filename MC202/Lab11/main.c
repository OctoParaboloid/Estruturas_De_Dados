#include "Grafo.h"





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



int main(int argc, char **argv)
{

    le_grafo(argv[1]);


    return(0);
}
