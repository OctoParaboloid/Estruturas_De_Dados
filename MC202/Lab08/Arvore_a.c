#include "ArvoreBinaria.h"
#include "ArvoreBinaria.c"




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

  espelho(T);
  output(T);

  DestroiArvoreBinaria(&T);

  return(0);
}
