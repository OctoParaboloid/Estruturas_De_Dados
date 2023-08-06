#include "ArvoreBinaria.h"
#include "ArvoreBinaria.c"


int IPLen(NoArvoreBinaria *T) //assumindo arvore nao vazia
{
    if (T == NULL) return(-1);

    int ne = IPLen(T->esq);   //serao zeros se é folha
    int nd = IPLen(T->dir);
    if (ne == -1 && nd == -1) return(0); //eh folha 0 caminhos

    if (ne >= 0) ne = ne + n_nos(T->esq); //relacao recursiva: +1 pra todos os caminhos da subarvore
    if (nd >= 0) nd = nd + n_nos(T->dir);      //há n-1 caminhos para uma arvore com n nos; + o caminho da nova raiz pro ramo

    if (ne == -1 || nd == -1) return(max_2(ne, nd)); //considera o unico ramo nao-nulo


    return(ne + nd);
}

ArvoreBinaria *le_e_constroi(char *nomearq)
{
    FILE *f = fopen(nomearq, "r");

    int n;
    fscanf(f, "%d\n", &n);

    int **SimPos = (int **)calloc(2, sizeof(int *));

    SimPos[0] = (int *)calloc(n, sizeof(int));
    SimPos[1] = (int *)calloc(n, sizeof(int));
    int j;
    for (int i = 0; i < 2; i++)
    {
        for ( j = 0; j < n; j++)
        {
            fscanf(f, "%d ", &SimPos[i][j]);
        }

        fscanf(f, "\n");

    }
    ArvoreBinaria *T = ConstroiArvoreBinariaSimPos(SimPos[0], SimPos[1], n);

    free(SimPos[0]);
    free(SimPos[1]);
    free(SimPos);

    fclose(f);
    return(T);
}

int main(int argc, char **argv)
{
  ArvoreBinaria *T=NULL;

  T = le_e_constroi(argv[1]);

  int ipl = IPLen(T);

  printf("%d", ipl);

  DestroiArvoreBinaria(&T);

  return(0);
}
