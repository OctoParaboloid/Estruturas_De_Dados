#include "ArvoreBinaria.h"
#include "ArvoreBinaria.c"





int n_nos(NoArvoreBinaria *T)
{
    if (T == NULL) return(0);
    return(1 + n_nos(T->esq) + n_nos(T->dir));
}


void pre_ord(NoArvoreBinaria *T)
{
    if (T != NULL)
    {
        printf("%d ", T->info);
        pre_ord(T->esq);
        pre_ord(T->dir);
    }
}

void pos_ord(NoArvoreBinaria *T)
{
    if (T != NULL)
    {
        pos_ord(T->esq);
        pos_ord(T->dir);
        printf("%d ", T->info);
    }
}

void in_ord(NoArvoreBinaria *T)
{
    if (T != NULL)
    {
        in_ord(T->esq);
        printf("%d ", T->info);
        in_ord(T->dir);
    }
}


int max(int n1, int n2)
{
    if (n1 > n2) return(n1);

    return(n2);
}

void espelho(NoArvoreBinaria *T)
{
    if (T != NULL)
    {
        NoArvoreBinaria *aux= T->esq;
        T->esq = T->dir;
        T->dir = aux;

        espelho(T->esq);
        espelho(T->dir);
    }
}

void output(NoArvoreBinaria *T)
{
    pre_ord(T);
    printf("\n");
    in_ord(T);
    printf("\n");
    pos_ord(T);
}


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

  DestroiArvoreBinaria(&T);

  return(0);
}
