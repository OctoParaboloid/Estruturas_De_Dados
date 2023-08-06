#include <stdio.h>
#include <stdlib.h>

                /* eu li errado antes de fazer, achei que eram tanques ao inves de bombas
                 * mas no fim da no mesmo. O raio da bomba seria o alcance do tanques. 
                 * Pra atividade 1 n importa. */
typedef struct t
{
    int x;
    int y;
    int r;
} tanque;


int distTab (int x1, int x2)
{
    int res = x1 - x2;
    if (res < 0)
    {
        return(-res);
    }else
    {
        return(res);
    }
}

int seguro(int n, tanque *t, int pos[2])
{
    int px = pos[0];
    int py = pos[1];
    int tx;
    int ty;
    int r;
    
    for (int i = 0; i < n; i++)
    {
        tx = t[i].x;
        ty = t[i].y;
        r = t[i].r;
        if (distTab(px, tx) > r || distTab(py, ty) > r) /* checa se esta no raio de explosao */
        {
            continue;
        }else
        {
            return(0);
        }
    }
    return(1);
}

tanque * Cria_Tanques(int n)
{
    tanque *vetorTanques = calloc(n, sizeof(tanque));
    return (vetorTanques);
}

void preenche_Tanque(int x, int y, int r, tanque *t)
{
   t->x = x;
   t->y = y;
   t->r = r;
}


int positivo_dentro(int x, int y, int r, int tabuleiro[2])
{
    if (x < 0 || y < 0 || r < 0) /*checando positividade*/
    {
        return(0);
    }
    if (x >= tabuleiro[0] || y >= tabuleiro[1]) /* como o indice comeca do zero, x e y tem que ser menores. */
    {
        return(0);
    }
    return(1);
}




int main()
{
    int tabuleiro[2];
    
    if (scanf("%dx%d", &tabuleiro[0], &tabuleiro[1]))
    { /* tabuleiro */
        setbuf(stdin, NULL);
    } else {        /*else captura input nao-digito*/
        printf("-1");
        exit(0);
    }
    if (tabuleiro[0] <= 0 || tabuleiro[1] <= 0){
        printf("-1");
        exit(0);                               /* tabuleiro nao pode ser vazio nem negativo*/
    }
    
    int n;  /* numero de bombas */
    if (scanf("%d", &n))
    {
        setbuf(stdin, NULL);
    }else
    {
        printf("-1");
        exit(0);
    }
    if (n <= 0)
    {
        printf("-1");
        exit(0);
    }

    /* criando e preenchendo o vetor com os tanques */
    tanque *vetor_Tanques = Cria_Tanques(n);
    for (int i = 0; i < n; i++) /* vai pedir coords e raio para cada tanque */
    {
        int x;
        int y;
        int r;

        if (scanf("%d %d %d", &x, &y, &r)) /* checa se sao de fato digitos*/
        {
        setbuf(stdin, NULL);
        }else
        {
            free(vetor_Tanques);
            printf("-1");
            exit(0);
        }                               /*...*/
        
        if (positivo_dentro(x, y, r, tabuleiro) == 0) /* checa se sao positivos e dentro do tabuleiro */
        {
            free(vetor_Tanques);
            printf("-1");
            exit(0);
        }

        preenche_Tanque(x, y, r, &vetor_Tanques[i]);
    }
    /*tabuleiro com tanques configurados */

    int xy[2];
    if (scanf("%d %d", &xy[0], &xy[1]))
    {
        setbuf(stdin, NULL);
    }else
    {
        free(vetor_Tanques);
    }

    if ( xy[0] < 0 || xy[0] > tabuleiro[0] /* checando se positivos e dentro do tabuleiro */
      || xy[1] < 0 || xy[1] > tabuleiro[1])
    {
        free(vetor_Tanques);
        printf("-1");
        exit(0);
    }
    /* A PARTIR DAQUI, INPUTS VALIDOS */

    if (seguro(n, vetor_Tanques, tabuleiro) == 1)
    {
        printf("Seguro");
    }else 
    {
        printf("Perigoso");
    }
    free(vetor_Tanques);

    return(0);
}
