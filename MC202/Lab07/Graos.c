#include "ArvoreBinaria.h" //deixando somente essa da erro de 'undefined reference'
#include "ArvoreBinaria.c"  // e com esse, 'multiple definitions'. mas pelo menos passa nos outros testes

/* Constrói uma árvore binária a partir de dois percursos dados.

   gcc ConstroiArvoreBinaria.c -o ConstroiArvoreBinaria

*/


/*Reaproveitei o código do professor ArvoreBinaria.c e ArvoreBinaria.h*/


/*fiz apenas as funcoes max_2(), max_3() e SomaMax() e le_e_constroi()*/
                                            /* ________________*/
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
    //int Sm_Pm[2];

    if (T == NULL)
    {
        Sm_Pm[0] = 0;
        Sm_Pm[1] = 0;
        return(Sm_Pm);
    }

    int *SP_esq = SomaMax(T->esq);
    int *SP_dir = SomaMax(T->dir);

    Sm_Pm[0] = max_3(SP_esq[0], SP_dir[0], T->info+SP_esq[1]+SP_dir[1]);
    Sm_Pm[1] = max_3(T->info+SP_esq[1], T->info+SP_dir[1], 0);

    free(SP_esq);
    free(SP_dir);

    return(Sm_Pm);
}
                                            /* ________________*/

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

    //ImprimeArvoreBinaria(T, 0, Altura(T));
  /* ________________*/

  int *SM = SomaMax(T);
  printf("%d", SM[0]);
  /* ________________*/


    free(SM);

  DestroiArvoreBinaria(&T);

  return(0);
}
