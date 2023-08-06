#include "FilaPrioridade.h"
//#include "FilaPrioridade.c"

void le_arquivo(char *nomearq)
{
    FILE *f = fopen(nomearq, "r");
    int n;
    fscanf(f,"%d\n", &n);

    fila_prioridade *fila = cria_fila_prio(100);

    char prim;
    for (int i = 0; i < n; i++)
    {

        fscanf(f, "%c", &prim);
        if (prim == 'I')
        {
            fscanf(f, " ");
            char novo_cliente[50];
            int i = 0;
            fscanf(f, "%c", &novo_cliente[i]);
            while (novo_cliente[i] != ' ')
            {
                i++;
                fscanf(f, "%c", &novo_cliente[i]);
            }
            novo_cliente[i] = '\0';

            int prioridade_nova;
            fscanf(f, "%d", &prioridade_nova);

            insere_cliente(fila, novo_cliente, prioridade_nova);

            fscanf(f, "\n");
            continue;

        }
        if (prim == 'M')
        {
            fscanf(f, " ");
            char b_cliente[50];
            int i = 0;
            fscanf(f, "%c", &b_cliente[i]);
            while (b_cliente[i] != ' ')
            {
                i++;
                fscanf(f, "%c", &b_cliente[i]);
            }
            b_cliente[i] = '\0';

            int prioridade_nova;
            fscanf(f, "%d", &prioridade_nova);

            busca_muda_cliente(fila, b_cliente, prioridade_nova);

            fscanf(f, "\n");
            continue;
        }
        if (prim == 'P')
        {
            imprime_p_u(fila);
            fscanf(f, "\n");
            continue;
        }
        if (prim == 'L')
        {
            remove_prim_fila(fila);
            fscanf(f, "\n");
            continue;
        }
        if (prim == 'D')
        {
            remove_ult_fila(fila);
            fscanf(f, "\n");
            continue;
        }
        continue;
    }
    destroi_fila(fila);
    fclose(f);
}




int main(int argc, char **argv)
{
    le_arquivo(argv[1]);


    return(0);
}
