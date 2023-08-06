#include <stdio.h>
#include <stdlib.h>

                    /* Para a atividade b, aproveitei o codigo da atividade a
                     * Apenas modifiquei a funcao seguro() agora chamada de ufa_boom() */
typedef struct t
{
    int x;
    int y;
    int r;
} tanque;

typedef struct tboom
{
    int x;
    int y;
    int resis;
} tanque_boom;

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

int ufa_boom(int n, tanque *t, tanque_boom tboom)
{
    int px = tboom.x;
    int py = tboom.y;
    int resis = tboom.resis;
    int tx;
    int ty;
    int r;
    
    for (int i = 0; i < n; i++)
    {
        tx = t[i].x;
        ty = t[i].y;
        r = t[i].r;
        if (distTab(px, tx) > r || distTab(py, ty) > r) /* checa se esta fora do raio de explosao */
        {
            continue;
        }else
        {
            resis = resis - 1 ; /* o tanque perde resistencia */
        }
    }
    /* checagem completa. falta checar se sobrou alguma resistencia ao nosso tanque. */
    
    if (resis > 0)
    {
        return(1); /*ufa*/
    }else
    {
        return(0); /*boom*/
    }
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
        
        if (positivo_dentro(x, y, r, tabuleiro) == 0)/* checa se sao positivos e dentro do tabuleiro */
        {
            free(vetor_Tanques);
            printf("-1");
            exit(0);
        }
        preenche_Tanque(x, y, r, &vetor_Tanques[i]);
    }
    /*tabuleiro com tanques configurados */

    tanque_boom tboom;
    if (scanf("%d %d %d", &tboom.x, &tboom.y, &tboom.resis))
    {
        setbuf(stdin, NULL);
    }else
    {
        free(vetor_Tanques);
        printf("-1");
        exit(0);
    }

    if ( tboom.x < 0 || tboom.x > tabuleiro[0] /* checando se positivos e dentro do tabuleiro */
      || tboom.y < 0 || tboom.y > tabuleiro[1] || tboom.resis < 0)
    {
        free(vetor_Tanques);
        printf("-1");
        exit(0);
    }
    /* A PARTIR DAQUI, INPUTS VALIDOS */

    if (ufa_boom(n, vetor_Tanques, tboom) == 1)
    {
        printf("Ufa");
    }else 
    {
        printf("Boom");
    }
    free(vetor_Tanques);

    return(0);
}
