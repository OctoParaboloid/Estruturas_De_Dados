#include <stdio.h>
#include <stdlib.h>



//USADAS PARA DEBUGAR
void printa_vetor(int *v)
{
    for (int i = 0; i < v[0]; i++)
        printf("%d ", v[i]);
    printf("%d", v[v[0]]);
}

void printa_VF(int **VF, int n)
{
    for (int i = 0; i < n; i++)
    {
        printa_vetor(VF[i]);
        printf("\n");

    }
}

void printa_vetor_entrada(char *entrada_linha)
{
    for (int i = 0; i < 2*(entrada_linha[0]- 48)+1; i++)
    {
        printf("%c", entrada_linha[i]);
    }
    printf("\n");
}

//USADAS PARA DEBUGAR FIM



int **CriaVetorFilas(int n, char **entrada)
{
    int **v = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        int tam_k = (int)(entrada[i][0] - 48);
        v[i] = (int *)calloc(tam_k+1, sizeof(int));
        v[i][0] = tam_k;                            //primeiro valor indica quantos clientes
        for (int j = 1; j < tam_k+1; j++)
        {
            v[i][j] = (int)(entrada[i][2*j]-48);
        }
    }
    return(v);
}

char **cria_entrada(int n)
{
    char **entrada = (char **)calloc(n, sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        entrada[i] = (char *)calloc(199, sizeof(char));  //no maximo 100 numeros e 99 espacos entre cada
    }
    return(entrada);
}

int *intercala(int *v, int *w)
{
    int i = 1;
    int j = 1;
    int k = 1;
    int *intercalado = (int *)calloc( (1+(v[0] + w[0])) , sizeof(int));
    intercalado[0] = (v[0] + w[0]);
    while (i <= v[0] && j <= w[0])
    {
        if (v[i] < w[j])
        {
            intercalado[k] = v[i];
            i++;
            k++;
        }
        else
        {
            intercalado[k] = w[j];
            j++;
            k++;
        }
    }
    if (i > v[0]) //preencher com o restante de w
    {
        for (int jj = j; jj <= w[0]; jj++)
        {
            intercalado[k] = w[jj];
            k++;
        }
    }
    else     //preencher com o restante de v
    {
        for (int ii = i; ii <= v[0]; ii++)
        {
            intercalado[k] = v[ii];
            k++;
        }
    }
    return(intercalado);
}

void intercalado_output(int *intercalado)
{
    for (int i = 1; i < intercalado[0]; i++)
    {
        printf("%d ", intercalado[i]);
    }
    printf("%d", intercalado[intercalado[0]]);
}



int *vetor_intercalado(int **VF, int n_filas) //a ideia é intercalar iterativamente
{
    if (n_filas == 1) return(VF[0]);

    int tam_intercalado = VF[0][0];

    int *intercalado = (int *)calloc(tam_intercalado, sizeof(int));
    intercalado[0] = VF[0][0];

    for (int i = 1; i < VF[0][0]+1; i++)
    {
        intercalado[i] = VF[0][i];
    }
    //comeco com a primeira fila e vou iterando com as demais

    int c_filas_intercaladas = 1;
    int *intercalado_antigo = intercalado;
    while (c_filas_intercaladas < n_filas) //enquanto houver filas para serem intercaladas
    {
        intercalado = intercala(intercalado, VF[c_filas_intercaladas]); //o vetor intercalado atual
        free(intercalado_antigo);                           //libero o antigo que nao sera mais usado
        c_filas_intercaladas++;
    }

    return(intercalado);
}

void destroi_entrada(char **entrada, int n_filas)
{
    for (int i = 0; i < n_filas; i++)
    {
        free(entrada[i]);
    }
    free(entrada);
}

void destroi_VF(int **VF, int n_filas)
{
    for (int i = 0; i < n_filas; i++)
    {
        free(VF[i]);
    }
    free(VF);
}

int main()
{
    int n_filas;

    scanf("%d\n", &n_filas);
        if (n_filas > 0){

            char **entrada = cria_entrada(n_filas);

                    //--------LEITURA----------
            for (int i = 0; i < n_filas; i++)
            {
                fgets(entrada[i], 199, stdin);        //preencho cada fila com os clientes
            }
            //printa_entrada(entrada, n_filas);
                //--------FIM_LEITURA---------
            int **VF = CriaVetorFilas(n_filas, entrada);
            destroi_entrada(entrada, n_filas);

            int *intercalado_final = vetor_intercalado(VF, n_filas);
            intercalado_output(intercalado_final);

            destroi_VF(VF, n_filas);

    }

    return(0);
}
